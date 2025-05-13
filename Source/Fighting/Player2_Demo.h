//--------------------------------------------------------------------
// �t�@�C���� �FAPlayerCharacter.cpp
// �T�v       �F2P�̃f��
// �쐬��     �F0231�{��
// �X�V���e   �F4/15�@�쐬
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

	// ���@���F�Ȃ�
	// �߂�l�Fvoid
	// �������e�F�ړ�����
	virtual void Move()override;
	virtual void PadMove(const FInputActionValue&) override;

	virtual void Jump(float DeltaTime) override;

	// ���@���F�Ȃ�
	// �߂�l�Fvoid
	// �������e�F�U������
	virtual void AttackAction()override;

	// ���@���F�Ȃ�
	// �߂�l�Fvoid
	// �������e�F���z�֐���`
	virtual void InputMove()override;

	virtual void InputJump() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* _defaultMappingContext;//�C���v�b�g�̏ڍ׏��

	UPROPERTY(EditAnywhere, Category = Input)
	TMap<FName, TObjectPtr<UInputAction>> _InputActions;//�C���v�b�g�A�N�V��������

	UPROPERTY()
	APlayerController* _controller = nullptr;
};
