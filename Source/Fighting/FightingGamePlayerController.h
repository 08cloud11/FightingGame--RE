// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FightingGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTING_API AFightingGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	enum Direction
	{
		non,
		LLeft,
		Lower,
		LRight,
		Left,
		Center,
		Right,
		ULeft,
		Up,
		URight
	};

public:
	AFightingGamePlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void SetPlayerID(int _PlayerID = 0);

	UFUNCTION(BlueprintCallable) FString _InputLever(const float X = 0.f, const float Y = 0.f);

private:
	// コマンドの入力
	void _InputCommand();

private:
	const float _LeverCorrection = 0.08f;	// レバーの補正値
	/*APlayerBase* _OperatePlayer;*/

	Direction _InputDirection;

};
