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

	// ���@���F�Ȃ�
	// �߂�l�Fvoid
	// �������e�F�ړ�����
	virtual void Move()override;
	virtual void Move(float) override;

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
