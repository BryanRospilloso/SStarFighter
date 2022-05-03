// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Terrestre1.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AEnemigo_Terrestre1::AEnemigo_Terrestre1()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemigoMeshTerrestre(TEXT("/Game/Meshes/dicokka_high.dicokka_high"));
	EnemigoMesh->SetStaticMesh(EnemigoMeshTerrestre.Object);

}
