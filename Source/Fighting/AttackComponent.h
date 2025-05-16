// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "TestBullet.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTING_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//移動方向
	enum MoveDirection
	{
		Move_Left,
		Move_Right,
		Move_Up,
		Move_Down
	};

	//攻撃の種類
	enum CurrentAtkType
	{
		punch_weak,
		punch_medium,
		punch_strong,
		kick_weak,
		kick_medium,
		kick_strong
	};

	enum CharaType
	{
		charaA,
		charaB
	};

	struct AtkMoveLength
	{
		float punch_weak;
		float punch_medium;
		float punch_strong;
		float kick_weak;
		float kick_medium;
		float kick_strong;
	};

public:	
	UAttackComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//------------ゲッター-----------------

	bool Get_battack() const { return _battack; }

	//-------------------------------------

protected:
	virtual void BeginPlay() override;	

private:
	void MoveCol(float DeltaTime);

	// 引　数：なし
	// 戻り値：void
	// 処理内容：波動拳コマンド処理
	void Hadouken();

private:	
	UPROPERTY(EditAnywhere, Category = "Bullet")
	TSubclassOf<AActor> _atkactor = nullptr;

	UPROPERTY()
	AActor* _spawnactor = nullptr;

	AtkMoveLength _currentlength;

	MoveDirection _movedir;
	CurrentAtkType _atktype;

	int _actionflame;

	int _owneratkpower;

	bool _battack;

	//trueならパンチ、falseでキック
	bool _batkstate;
};
