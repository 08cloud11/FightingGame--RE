// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestBullet.generated.h"

class ACharactorBase;

UCLASS()
class FIGHTING_API ATestBullet : public AActor
{
	GENERATED_BODY()
	
public:
	//ˆÚ“®•ûŒü
	enum MoveDirection
	{
		Move_Left,
		Move_Right,
		Move_Up,
		Move_Down
	};

	enum CurretCharaType
	{
		charaA,
		charaB,
		None
	};

public:	
	ATestBullet();

	virtual void Tick(float DeltaTime) override;

	void Set_movedir(MoveDirection value) { _movedir = value; }
	void Set_currentchara(CurretCharaType charatype) { _curretchara = charatype; }

	CurretCharaType Get_currentchara() const { return _curretchara; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Move();

private:
	MoveDirection _movedir;
	CurretCharaType _curretchara = None;
};
