// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Aereo1.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AEnemigo_Aereo1::AEnemigo_Aereo1()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemigoMeshAereo(TEXT("/Game/Meshes/tie_UV.tie_UV"));
	EnemigoMesh->SetStaticMesh(EnemigoMeshAereo.Object);
	
}
