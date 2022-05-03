// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Acuatico.h"
#include "Time.h"

AEnemigo_Acuatico::AEnemigo_Acuatico()
{
}

void AEnemigo_Acuatico::Tick(float DeltaTime)
{
	srand(time(NULL));

	float rand1 = rand() % 40 - 20;
	float rand2 = rand() % 40 - 20;

	MoveSpeed = 250.0f;

	const FVector Move = FVector(rand1, rand2, 0.0f).GetClampedToMaxSize(1.0f);
	const FVector Movement = Move * MoveSpeed * DeltaTime;

	if (Movement.SizeSquared() > 1.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

	}

}
