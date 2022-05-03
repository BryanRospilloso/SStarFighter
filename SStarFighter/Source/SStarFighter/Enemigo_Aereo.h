// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "Enemigo_Aereo.generated.h"

UCLASS()
class SSTARFIGHTER_API AEnemigo_Aereo : public AEnemigo
{
	GENERATED_BODY()

public:
	AEnemigo_Aereo();

	virtual void Tick(float DeltaTime) override;
	
};
