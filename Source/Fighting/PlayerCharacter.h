// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharactorBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FIGHTING_API APlayerCharacter : public ACharactorBase
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	  
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// 引　数：なし
	// 戻り値：void
	// 処理内容：移動処理
	virtual void Move()override;
	virtual void Move(float) override;

	virtual void Jump(float DeltaTime) override;

	// 引　数：なし
	// 戻り値：void
	// 処理内容：攻撃処理
	virtual void AttackAction()override;

	// 引　数：なし
	// 戻り値：void
	// 処理内容：仮想関数定義
	virtual void InputMove()override;

	virtual void InputJump() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* _defaultMappingContext;//インプットの詳細情報

	UPROPERTY(EditAnywhere, Category = Input)
	TMap<FName, TObjectPtr<UInputAction>> _InputActions;//インプットアクションたち

	UPROPERTY()
	APlayerController* _controller = nullptr;
};
