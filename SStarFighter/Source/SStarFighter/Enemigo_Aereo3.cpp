// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Aereo3.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AEnemigo_Aereo3::AEnemigo_Aereo3()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemigoMeshAereo(TEXT("/Game/Meshes/Wraith_Raider_Starship.Wraith_Raider_Starship"));
	EnemigoMesh->SetStaticMesh(EnemigoMeshAereo.Object);
	
}
