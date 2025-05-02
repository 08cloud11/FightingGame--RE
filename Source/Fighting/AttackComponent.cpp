// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "CharactorBase.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
	: _actiontimer(0.0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
		
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(Cast<ACharactorBase>(GetOwner())->Get_atktype() != AttackType::None) MoveCol(DeltaTime);
}

void UAttackComponent::MoveCol(float DeltaTime)
{
	switch (Cast<ACharactorBase>(GetOwner())->Get_atktype())
	{
	case AttackType::punch_weak:
		WeekPunch(DeltaTime);

		break;
	case AttackType::punch_medium:
		WeekPunch(DeltaTime);

		break;
	case AttackType::punch_strong:
		WeekPunch(DeltaTime);

		break;
	case AttackType::kick_weak:
		WeekPunch(DeltaTime);

		break;
	case AttackType::kick_medium:
		WeekPunch(DeltaTime);

		break;
	case AttackType::kick_strong:
		WeekPunch(DeltaTime);

		break;
	}
}

void UAttackComponent::WeekPunch(float DeltaTime)
{
	if (_spawnactor == nullptr)
	{
		FVector pos = GetOwner()->GetActorLocation();

		FTransform spawnTr;
		spawnTr.SetLocation(pos);

		int value = Cast<ACharactorBase>(GetOwner())->Get_moveDir();

		_movedir = MoveDirection(value);

		_spawnactor = Cast<AActor>(GetWorld()->SpawnActor<AActor>(_atkactor, spawnTr));
		Cast<ATestBullet>(_spawnactor)->Set_movedir(ATestBullet::MoveDirection(_movedir));
		Cast<ATestBullet>(_spawnactor)->Set_currentchara(ATestBullet::CurretCharaType(
			Cast<ACharactorBase>(GetOwner())->Get_charatype()));
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

	_actiontimer += DeltaTime;

	if (_actiontimer > 0.8f)
	{
		_actiontimer = 0.0f;
		Cast<ACharactorBase>(GetOwner())->Set_atktype(AttackType::None);
		_spawnactor->Destroy();
		_spawnactor = nullptr;
	}
}