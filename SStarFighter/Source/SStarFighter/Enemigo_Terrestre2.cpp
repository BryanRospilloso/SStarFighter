// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Terrestre2.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AEnemigo_Terrestre2::AEnemigo_Terrestre2()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemigoMeshTerrestre(TEXT("/Game/Meshes/vehicle_tank18_rebelaxisforces_v1_LP.vehicle_tank18_rebelaxisforces_v1_LP"));
	EnemigoMesh->SetStaticMesh(EnemigoMeshTerrestre.Object);
	
}
