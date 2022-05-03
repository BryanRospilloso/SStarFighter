// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemigo.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class SSTARFIGHTER_API AEnemigo : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemigo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* EnemigoMesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float MoveSpeed;

public:
	FORCEINLINE class UStaticMeshComponent* GetEnemigoMesh() const { return EnemigoMesh; }
	FORCEINLINE class UCapsuleComponent* GetCapsuleCollision() const { return CapsuleCollision; }

};
