// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "CharactorBase.h"

UAttackComponent::UAttackComponent()
	: _actionflame(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
		
}

void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(Cast<ACharactorBase>(GetOwner())->Get_atktype() != AttackType::None) MoveCol(DeltaTime);
}

void UAttackComponent::MoveCol(float DeltaTime)
{
	//テスト用(パンチのステートならパンチの処理)
	if (Cast<ACharactorBase>(GetOwner())->Get_atktype() == AttackType::punch_weak
		|| Cast<ACharactorBase>(GetOwner())->Get_atktype() == AttackType::punch_medium
		|| Cast<ACharactorBase>(GetOwner())->Get_atktype() == AttackType::punch_strong)	{
		_batkstate = true;
	}
	else{
		_batkstate = false;
	}

	if (Cast<ACharactorBase>(GetOwner())->Get_atktype() == AttackType::hadouken)
	{
		Hadouken();
	}

	switch (_batkstate)
	{
	case true:

		break;

	case false:


		break;
	}
}

void UAttackComponent::Hadouken()
{
	_actionflame++;
	
	if (_actionflame < 35) return;
	else if (_spawnactor == nullptr)
	{
		FVector pos = GetOwner()->GetActorLocation();

		FTransform spawnTr;
		spawnTr.SetLocation(pos);

		int value = Cast<ACharactorBase>(GetOwner())->Get_moveDir();
		_movedir = MoveDirection(value);

		_spawnactor = Cast<AActor>(GetWorld()->SpawnActor<AActor>(_atkactor, spawnTr));
		Cast<ATestBullet>(_spawnactor)->Set_movedir(ATestBullet::MoveDirection(_movedir));
		Cast<ATestBullet>(_spawnactor)->Set_currentchara(
			Cast<ACharactorBase>(GetOwner())->Get_charatype());
	}

	FVector bulletpos = _spawnactor->GetActorLocation();

	switch (_movedir)
	{
	case UAttackComponent::Move_Left:

		_spawnactor->SetActorLocation(FVector(bulletpos.X, bulletpos.Y - 10.0, bulletpos.Z));
		break;

	case UAttackComponent::Move_Right:

		_spawnactor->SetActorLocation(FVector(bulletpos.X, bulletpos.Y + 10.0, bulletpos.Z));
		break;
	}

	if (_actionflame > 90)
	{
		_actionflame = 0;
		Cast<ACharactorBase>(GetOwner())->Set_atktype(AttackType::None);
		_spawnactor->Destroy();
		_spawnactor = nullptr;
	}
}