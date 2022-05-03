// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Misil.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AProjectile_Misil::AProjectile_Misil()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileBalaMesh(TEXT("/Game/Meshes/SeaDart.SeaDart"));
	ProjectileMesh->SetStaticMesh(ProjectileBalaMesh.Object);

	ProjectileSpeed = 1200.0f;

}

void AProjectile_Misil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(CurrentLocation.X, CurrentLocation.Y + (ProjectileSpeed * DeltaTime), CurrentLocation.Z);

	this->SetActorLocation(NewLocation);
	CurrentLocation = NewLocation;

}
