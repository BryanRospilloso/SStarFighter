// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Rayo.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AProjectile_Rayo::AProjectile_Rayo()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileBalaMesh(TEXT("/Game/Meshes/LaserBolt.LaserBolt"));
	ProjectileMesh->SetStaticMesh(ProjectileBalaMesh.Object);

	ProjectileSpeed = 1250.0f;

}

void AProjectile_Rayo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(CurrentLocation.X, CurrentLocation.Y + (ProjectileSpeed * DeltaTime), CurrentLocation.Z);

	this->SetActorLocation(NewLocation);
	CurrentLocation = NewLocation;

}
