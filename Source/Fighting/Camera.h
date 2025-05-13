// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h""
#include "GameFramework/Actor.h"
#include "vector3.h
#include "Camera.generated.h"

UCLASS()
class FIGHTING_API ACamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACamera();
	~ACamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AActor* pPlayer[];
	AActor* pWall[];

	Vector3 InitialPosition
};
