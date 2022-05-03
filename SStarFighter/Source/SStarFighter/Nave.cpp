// Fill out your copyright notice in the Description page of Project Settings.


#include "Nave.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ANave::ANave()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	NaveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nave Mesh"));
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));

	NaveMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MaxVelocity = 500.0f;
	Current_X_Velocity = 0.0f;
	Current_Y_Velocity = 0.0f;

	//ProjectileBala

	bBalaIsFiring = false;
	FireBalaRate = 0.25f;
	BalaTimeSinceLastShot = 0.0f;

	//ProjectileRayo

	bRayoIsFiring = false;
	FireRayoRate = 0.25f;
	RayoTimeSinceLastShot = 0.0f;

	//ProjectileMisil

	bMisilIsFiring = false;
	FireMisilRate = 0.25f;
	MisilTimeSinceLastShot = 0.0f;

	//ProjectileBomba

	bBombaIsFiring = false;
	FireBombaRate = 0.25f;
	BombaTimeSinceLastShot = 0.0f;

	const FVector MoveDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);

	const FRotator FireRotation = MoveDirection.Rotation();
	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		//FTransform SpawnLocation;
		// spawn the projectile

		ColaProyectiles.Push(World->SpawnActor<AProjectile>(SpawnLocation, FireRotation));
		ColaProyectiles.Push(World->SpawnActor<AProjectile>(SpawnLocation, FireRotation));
		ColaProyectiles.Push(World->SpawnActor<AProjectile>(SpawnLocation, FireRotation));
		ColaProyectiles.Push(World->SpawnActor<AProjectile>(SpawnLocation, FireRotation));
		ColaProyectiles.Push(World->SpawnActor<AProjectile>(SpawnLocation, FireRotation));

		//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation(X, Y) = %s, %s FireRotation(X, Y) =  s, s"), SpawnLocation.X, SpawnLocation.Y);
		//UE_LOG(LogTemp, Warning, TEXT("World not nullptr"));
	}

}

// Called when the game starts or when spawned
void ANave::BeginPlay()
{
	Super::BeginPlay();

	Current_Location = this->GetActorLocation();
	Current_Rotation = this->GetActorRotation();

	bHit = false;
	bDead = false;

	OnActorBeginOverlap.AddDynamic(this, &ANave::OnBeginOverLap);
	
}

// Called every frame
void ANave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Current_X_Velocity != 0.0f || Current_Y_Velocity != 0.0f)
	{
		New_Location = FVector(Current_Location.X + (Current_X_Velocity * DeltaTime), 
			Current_Location.Y + (Current_Y_Velocity * DeltaTime), 0);

		this->SetActorLocation(New_Location);
		
		Current_Location = New_Location;

	}

	if (Current_X_Velocity > 0.1f)
	{
		this->SetActorRotation(FRotator(Current_Rotation.Pitch + 20.0f, Current_Rotation.Yaw, Current_Rotation.Roll));

	}

	else if (Current_X_Velocity < -0.1f)
	{
		this->SetActorRotation(FRotator(Current_Rotation.Pitch - 20.0f, Current_Rotation.Yaw, Current_Rotation.Roll));

	}

	else {
		this->SetActorRotation(FRotator(Current_Rotation));

	}

	if (this->GetActorLocation().X > Field_Width)
	{
		Current_Location = FVector(Field_Width - 1, Current_Location.Y, Current_Location.Z);

	}

	if (this->GetActorLocation().X < -Field_Width)
	{
		Current_Location = FVector(-Field_Width + 1, Current_Location.Y, Current_Location.Z);

	}

	if (this->GetActorLocation().Y > Field_Height)
	{
		Current_Location = FVector(Current_Location.X, Field_Height - 1, Current_Location.Z);

	}

	if (this->GetActorLocation().Y < -Field_Height)
	{
		Current_Location = FVector(Current_Location.X, -Field_Height + 1, Current_Location.Z);

	}

	//ProjectileBala

	if (bBalaIsFiring)
	{
		if (BalaTimeSinceLastShot > FireBalaRate)
		{
			FireWeaponBala();
			BalaTimeSinceLastShot = 0.0f;
		}
	}

	BalaTimeSinceLastShot += DeltaTime;

	//ProjectileRayo

	if (bRayoIsFiring)
	{
		if (RayoTimeSinceLastShot > FireRayoRate)
		{
			FireWeaponRayo();
			RayoTimeSinceLastShot = 0.0f;
		}
	}

	RayoTimeSinceLastShot += DeltaTime;

	//ProjectileMisil

	if (bMisilIsFiring)
	{
		if (MisilTimeSinceLastShot > FireMisilRate)
		{
			FireWeaponMisil();
			MisilTimeSinceLastShot = 0.0f;
		}
	}

	MisilTimeSinceLastShot += DeltaTime;

	//ProjectileBomba

	if (bBombaIsFiring)
	{
		if (BombaTimeSinceLastShot > FireBombaRate)
		{
			FireWeaponBomba();
			BombaTimeSinceLastShot = 0.0f;
		}
	}

	BombaTimeSinceLastShot += DeltaTime;

}

// Called to bind functionality to input
void ANave::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveUp"), this, &ANave::MoveUp);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ANave::MoveRight);

	PlayerInputComponent->BindAction(FName("FireBala"), IE_Pressed, this, &ANave::StartFiringBala);
	PlayerInputComponent->BindAction(FName("FireBala"), IE_Released, this, &ANave::StopFiringBala);

	PlayerInputComponent->BindAction(FName("FireRayo"), IE_Pressed, this, &ANave::StartFiringRayo);
	PlayerInputComponent->BindAction(FName("FireRayo"), IE_Released, this, &ANave::StopFiringRayo);

	PlayerInputComponent->BindAction(FName("FireMisil"), IE_Pressed, this, &ANave::StartFiringMisil);
	PlayerInputComponent->BindAction(FName("FireMisil"), IE_Released, this, &ANave::StopFiringMisil);

	PlayerInputComponent->BindAction(FName("FireBomba"), IE_Pressed, this, &ANave::StartFiringBomba);
	PlayerInputComponent->BindAction(FName("FireBomba"), IE_Released, this, &ANave::StopFiringBomba);

}

void ANave::MoveUp(float AxisValue)
{
	Current_X_Velocity = MaxVelocity * AxisValue;
}

void ANave::MoveRight(float AxisValue)
{
	Current_Y_Velocity = MaxVelocity * AxisValue;

}

//ProjectileBala

void ANave::StartFiringBala()
{
	bBalaIsFiring = true;

}

void ANave::StopFiringBala()
{
	bBalaIsFiring = false;

}

void ANave::FireWeaponBala()
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectileBala = GetWorld()->SpawnActor(Projectile_Bala_BP,
		&Current_Location, &Current_Rotation, Params);

}

//ProjectileRayo

void ANave::StartFiringRayo()
{
	bRayoIsFiring = true;

}

void ANave::StopFiringRayo()
{
	bRayoIsFiring = false;

}

void ANave::FireWeaponRayo()
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectileRayo = GetWorld()->SpawnActor(Projectile_Rayo_BP,
		&Current_Location, &Current_Rotation, Params);

}

//ProjectileMisil

void ANave::StartFiringMisil()
{
	bMisilIsFiring = true;

}

void ANave::StopFiringMisil()
{
	bMisilIsFiring = false;

}

void ANave::FireWeaponMisil()
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectileBomba = GetWorld()->SpawnActor(Projectile_Misil_BP,
		&Current_Location, &Current_Rotation, Params);

}

//ProjectileBomba

void ANave::StartFiringBomba()
{
	bBombaIsFiring = true;

}

void ANave::StopFiringBomba()
{
	bBombaIsFiring = false;

}

void ANave::FireWeaponBomba()
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectileMisil = GetWorld()->SpawnActor(Projectile_Bomba_BP,
		&Current_Location, &Current_Rotation, Params);

}

void ANave::OnBeginOverLap(AActor* PlayerActor, AActor* OtherActor)
{
}

