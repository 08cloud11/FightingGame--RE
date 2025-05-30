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
		int Continuation,	// éùë±
		int Stiffness,		// çdíº
		int Stiffness_Hit,	// ÉqÉbÉgçdíº
		int Stiffness_Fuar, // ÉKÅ[Éhçdíº
		int Damage,			// É_ÉÅÅ[ÉW
		FString Property,	//  
		float Distance_Guard				// ÉKÅ[Éhãóó£, 
		);
private:

	bool IsAttack;

	// êîílån
	int Occurrence;		// î≠ê∂ÉtÉåÅ[ÉÄ
	int Continuation;	// éùë±
	int Stiffness;		// çdíº
	int Stiffness_Hit;	// ÉqÉbÉgçdíº
	int Stiffness_Fuard;// ÉKÅ[Éhçdíº
	int AttackTimer;
	
	int Damage;			// É_ÉÅÅ[ÉW
	FString Property;	// 

	float Distance_Guard;				// ÉKÅ[Éhãóó£

	UBoxComponent* OccurrenceCollision;	// î≠ê∂ëOÇÃÇ†ÇΩÇËîªíË
	UBoxComponent* ContinuationCollsion;// çdíºíÜÇÃÇ†ÇΩÇËîªíË

	UBoxComponent* StiffnessCollision;// çUåÇÇ†ÇΩÇËîªíË

	
};
