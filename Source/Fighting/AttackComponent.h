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

public:	
	UAttackComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 引　数：なし
	// 戻り値：void
	//// 処理内容：攻撃に必要な諸々の値を設定
	//void Set_Atkvalues(MoveDirection movedir, AttackType atkmode, int atkpower) {
	//	_movedir = movedir;
	//	_atktype = atkmode;
	//	_owneratkpower = atkpower;

	//	_battack = true;

	//	FVector pos = GetOwner()->GetActorLocation();
	//	FTransform spawnTr;
	//	spawnTr.SetLocation(pos);

	//	_spawnactor = Cast<ATestBullet>(GetWorld()->SpawnActor<AActor>(_atkactor, spawnTr));
	//	_spawnactor->Set_movedir(ATestBullet::MoveDirection(_movedir));
	//	_spawnactor->Set_currentchara(ATestBullet::CurretCharaType(charaB));
	//}

	bool Get_battack() const { return _battack; }

protected:
	virtual void BeginPlay() override;	

private:
	void MoveCol(float DeltaTime);

	void WeekPunch(float DeltaTime);

private:	
	UPROPERTY(EditAnywhere, Category = "Bullet")
	TSubclassOf<AActor> _atkactor = nullptr;

	UPROPERTY()
	AActor* _spawnactor = nullptr;

	MoveDirection _movedir;
	CurrentAtkType _atktype;

	float _actiontimer;

	int _owneratkpower;

	bool _battack;
};
