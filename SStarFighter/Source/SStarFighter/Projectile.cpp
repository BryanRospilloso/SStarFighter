// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));

	ProjectileMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	bHit = false;
	bDestroy = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = this->GetActorLocation();

	OnActorBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverLap);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnBeginOverLap(AActor* ProjectileActor, AActor* OtherActor)
{
}
