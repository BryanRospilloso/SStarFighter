// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Projectile.h"
#include "Cola.h"
#include "Projectile_Bala.h"
#include "Projectile_Rayo.h"
#include "Projectile_Misil.h"
#include "Projectile_Bomba.h"
#include "Nave.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class SSTARFIGHTER_API ANave : public APawn
{
	GENERATED_BODY()

		Cola<class AProjectile*> ColaProyectiles;

public:
	// Sets default values for this pawn's properties
	ANave();

	void MoveUp(float AxisValue);

	void MoveRight(float AxisValue);

	UPROPERTY(EditAnywhere)
		float MaxVelocity;

	float Current_X_Velocity;
	float Current_Y_Velocity;

	FVector Current_Location;
	FRotator Current_Rotation;
	FVector New_Location;

	UPROPERTY(EditAnywhere)
		float Field_Width;

	UPROPERTY(EditAnywhere)
		float Field_Height;

	//ProjectileBala

	void FireWeaponBala();
	void StartFiringBala();
	void StopFiringBala();
	bool bBalaIsFiring;
	float FireBalaRate;
	float BalaTimeSinceLastShot;

	//ProjectileRayo

	void FireWeaponRayo();
	void StartFiringRayo();
	void StopFiringRayo();
	bool bRayoIsFiring;
	float FireRayoRate;
	float RayoTimeSinceLastShot;

	//ProjectileMisil

	void FireWeaponMisil();
	void StartFiringMisil();
	void StopFiringMisil();
	bool bMisilIsFiring;
	float FireMisilRate;
	float MisilTimeSinceLastShot;

	//ProjectileBomba

	void FireWeaponBomba();
	void StartFiringBomba();
	void StopFiringBomba();
	bool bBombaIsFiring;
	float FireBombaRate;
	float BombaTimeSinceLastShot;

	//**********

	bool bHit;
	bool bDead;

	UFUNCTION()
		void OnBeginOverLap(AActor* PlayerActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile_Bala> Projectile_Bala_BP;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile_Rayo> Projectile_Rayo_BP;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile_Misil> Projectile_Misil_BP;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile_Bomba> Projectile_Bomba_BP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* NaveMesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//***********************
	UPROPERTY()
		FVector GunOffset;
	float FireForwardValue;
	float FireRightValue;

public:
	FORCEINLINE class UStaticMeshComponent* GetNaveMesh() const { return NaveMesh; }
	FORCEINLINE class UCapsuleComponent* GetCapsuleCollision() const { return CapsuleCollision; }

};
