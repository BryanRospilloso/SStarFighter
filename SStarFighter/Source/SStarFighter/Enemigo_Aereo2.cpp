// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Aereo2.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AEnemigo_Aereo2::AEnemigo_Aereo2()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemigoMeshAereo(TEXT("/Game/Meshes/SpaceShip.SpaceShip"));
	EnemigoMesh->SetStaticMesh(EnemigoMeshAereo.Object);
	
}
