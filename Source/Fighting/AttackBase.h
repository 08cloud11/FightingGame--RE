// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "AttackBase.generated.h"

UCLASS()
class FIGHTING_API AAttackBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAttackBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InputAttack();

	int GetDamage();

	void SetOccurrenceCollision();

	void SetOccurrenceCollision(FString Delete);

	void SetStiffnessCollision();

	void SetStiffnessCollision(FString Delete);

	void SetContinuationCollision();

	void SetContinuationCollision(FString Delete);

public:
	void AddAttackTimer();

	const bool IsOccurrenceFrame();

	const bool IsContinuation();

	const bool IsWholeFrame();

	void ResetAttackTimer();

	int GetAttackTimer();
	
	float GetGuardDistance();

	int HitStiffness();

	int GuardStiffness();

public:
	UFUNCTION(BlueprintCallable)
	void SetOccurrenceCollision(UBoxComponent* UBoxCollision);

	UFUNCTION(BlueprintCallable)
	void SetContinuationCollision(UBoxComponent* UBoxCollision);

	UFUNCTION(BlueprintCallable)
	void SetStiffnessCollision(UBoxComponent* UBoxCollision);

	UFUNCTION(BlueprintCallable)
	void SetAttackInfomation(int Occurrence,
		int Continuation,	// 持続
		int Stiffness,		// 硬直
		int Stiffness_Hit,	// ヒット硬直
		int Stiffness_Fuar, // ガード硬直
		int Damage,			// ダメージ
		FString Property,	//  
		float Distance_Guard				// ガード距離, 
		);
private:

	bool IsAttack;

	// 数値系
	int Occurrence;		// 発生フレーム
	int Continuation;	// 持続
	int Stiffness;		// 硬直
	int Stiffness_Hit;	// ヒット硬直
	int Stiffness_Fuard;// ガード硬直
	int AttackTimer;
	
	int Damage;			// ダメージ
	FString Property;	// 

	float Distance_Guard;				// ガード距離

	UBoxComponent* OccurrenceCollision;	// 発生前のあたり判定
	UBoxComponent* ContinuationCollsion;// 硬直中のあたり判定

	UBoxComponent* StiffnessCollision;// 攻撃あたり判定

	
};
