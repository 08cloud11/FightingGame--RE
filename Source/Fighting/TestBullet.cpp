// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBullet.h"

// Sets default values
ATestBullet::ATestBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

void ATestBullet::Move()
{
	FVector pos = GetActorLocation();

	switch (_movedir)
	{
	case ATestBullet::Move_Left:

		SetActorLocation(FVector(pos.X, pos.Y - 10.0, pos.Z));
		break;

	case ATestBullet::Move_Right:

		SetActorLocation(FVector(pos.X, pos.Y + 10.0, pos.Z));
		break;
	}
}