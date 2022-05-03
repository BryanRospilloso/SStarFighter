// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Acuatico1.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AEnemigo_Acuatico1::AEnemigo_Acuatico1()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemigoMeshAcuatico(TEXT("/Game/Meshes/nitro_sub.nitro_sub"));
	EnemigoMesh->SetStaticMesh(EnemigoMeshAcuatico.Object);

}
