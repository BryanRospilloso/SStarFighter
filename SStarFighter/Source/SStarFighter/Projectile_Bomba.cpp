// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Bomba.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AProjectile_Bomba::AProjectile_Bomba()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileBalaMesh(TEXT("/Game/Meshes/tsar_bomb.tsar_bomb"));
	ProjectileMesh->SetStaticMesh(ProjectileBalaMesh.Object);

	ProjectileSpeed = 800.0f;

}

void AProjectile_Bomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(CurrentLocation.X, CurrentLocation.Y + (ProjectileSpeed * DeltaTime), CurrentLocation.Z);

	this->SetActorLocation(NewLocation);
	CurrentLocation = NewLocation;

}
