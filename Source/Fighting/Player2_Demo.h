//--------------------------------------------------------------------
// ファイル名 ：APlayerCharacter.cpp
// 概要       ：2Pのデモ
// 作成者     ：0231本間
// 更新内容   ：4/15　作成
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "CharactorBase.h"
#include "EnhancedInputSubsystems.h"
#include "Player2_Demo.generated.h"

UCLASS()
class FIGHTING_API APlayer2_Demo : public ACharactorBase
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetInput(APlayerController* controller) 
	{
		_controller = controller;

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_controller->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(_defaultMappingContext, 1);
		}
	}

protected:
	virtual void BeginPlay() override;

	// 引　数：なし
	// 戻り値：void
	// 処理内容：移動処理
	virtual void Move()override;
	virtual void PadMove(const FInputActionValue&) override;

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
