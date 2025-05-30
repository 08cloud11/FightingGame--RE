// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Engine/EngineTypes.h"
#include "AttackBase.h"
#include "CharaBase.generated.h"

UCLASS()
class FIGHTING_API ACharaBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACharaBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ���܂��Ă���U���̏���`����
	AAttackBase* NowAttackInfo();

// �u���[�v�����g�n�̊֐�
public:
	// HP�̐ݒ�
	UFUNCTION(BlueprintCallable)
	void SetHP(int _setHP);

	// HP�̎擾
	UFUNCTION(BlueprintCallable)
	const int GetHP();

	UFUNCTION(BlueprintCallable)
	void SetEnemy(APawn* EnemyPawn);

	// �����蔻��n�̏���
	UFUNCTION(BlueprintCallable)
	void OverlapBoxCollision(APawn* Pawn);

	// �U���n�̂����蔻����̐ݒ�
	UFUNCTION(BlueprintCallable)
	void SetAttackCollision(UBoxComponent* information, FString CollisionType, FString Part, FString strength, FString condition);

	// �U���n�̏����Z�b�g����
	UFUNCTION(BlueprintCallable)
	void SetAttackInfo(int Occurrence, 
	int Continuation,	// ����
	int Stiffness,		// �d��
	int Stiffness_Hit,	// �q�b�g�d��
	int Stiffness_Fuar, // �K�[�h�d��
	int Damage,			// �_���[�W
	FString Property,	//  
	float Distance_Guard,				// �K�[�h����, 
	FString Part, 
	FString strength, 
	FString condition);

	// �ړ��n�̃{�^���������ꂽ�Ƃ��ɌĂ΂��
	UFUNCTION(BlueprintCallable)
	void SetMoveDirection(bool Move_Right, bool Move_Left, bool Move_Up, bool Move_Down);

	// �A�^�b�N�n�̃{�^�����Ă΂ꂽ�Ƃ��ɌĂяo�����
	UFUNCTION(BlueprintCallable)
	void PushAttackButtom(FString Part, FString strength);

	UFUNCTION(BlueprintCallable)
	bool GetJump();

	UFUNCTION(BlueprintCallable)
	bool GetMove();

	UFUNCTION(BlueprintCallable)
	bool GetCrouch();

	void ShadySeam(float _fShadySeam);

	AAttackBase* GetAttackPointer();

	UFUNCTION(BlueprintCallable)
	APawn* GetEnemy() {
		return EnamyChara;
	}

private:
	void Move();

	// �������̓��͂����鎞�̃W�����v
	void Jump(auto SideDirecition);

	// �����W�����v
	void Jump();

	// �U���n
	void Attack();

	// ���Ⴊ��
	void Crouch();

	// �X�e�[�^�X��ύX����
	void ChangeState();

	// �����ڂ̕ύX
	void Visual();

	// �U���̌���
	AAttackBase* SearchAttack(FString Part, FString strength, FString condition);

	void stiffen();

private:
	APawn* EnamyChara;

	// �U���̕ϐ�
	TObjectPtr< AAttackBase > Punch_Weak;			// �����R�p��
	TObjectPtr< AAttackBase > Punch_During;			// �������p��
	TObjectPtr< AAttackBase > Punch_High;			// ������p��
	TObjectPtr< AAttackBase > Punch_Weak_Crouch;		// ���Ⴊ�݃R�p��
	TObjectPtr< AAttackBase > Punch_During_Crouch;	// ���Ⴊ�ݒ��p��
	TObjectPtr< AAttackBase > Punch_High_Crouch;		// ���Ⴊ�ݑ�p��
	TObjectPtr< AAttackBase > Punch_Weak_Sky;		// �󒆃R�p��
	TObjectPtr< AAttackBase > Punch_During_Sky;		// �󒆒��p��
	TObjectPtr< AAttackBase > Punch_High_Sky;		// �󒆑�p��

	TObjectPtr< AAttackBase > Kick_Weak;				// ������K
	TObjectPtr< AAttackBase > Kick_During;			// ������K
	TObjectPtr< AAttackBase > Kick_High;				// ������K
	TObjectPtr< AAttackBase > Kick_Weak_Crouch;		// ����
	TObjectPtr< AAttackBase > Kick_During_Crouch;	// ����
	TObjectPtr< AAttackBase > Kick_High_Crouch;		// �呫
	TObjectPtr< AAttackBase > Kick_Weak_Sky;			// �󒆏���
	TObjectPtr< AAttackBase > Kick_During_Sky;		// �󒆒���
	TObjectPtr< AAttackBase > Kick_High_Sky;			// �󒆑呫

	AAttackBase* Attacking;				// �U�����̕ϐ�

	int _HP;				// HP

	const float c_MoveSpeed = 30.f;	// �ړ����x
	const float c_JumpPower = 30.f;

	const int MaxJumpNum = 60;
	const int SinMax = 180;

	int _Stiffness;		// �d���t���[��
	bool _IsStiffness;

	bool _IsGuord;			// �K�[�h���邩
	bool _IsJump;		// �W�����v���Ă��邩
	bool _IsAttack;		// �U�����Ă��邩
	bool _IsCrouch;		// ���Ⴊ��ł��邩
	bool _IsRecive;		// �U�����󂯂Ă��邩
	bool _IsMoveing;

	FVector2D MoveDirection;

	// �̂��폜�\��
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_Weak;			// �����R�p��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_During;			// �������p��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_High;			// ������p��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_Weak_Crouch;		// ���Ⴊ�݃R�p��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_During_Crouch;	// ���Ⴊ�ݒ��p��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_High_Crouch;		// ���Ⴊ�ݑ�p��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_Weak_Sky;		// �󒆃R�p��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_During_Sky;		// �󒆒��p��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_High_Sky;		// �󒆑�p��


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_Weak;				// ������K

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_During;			// ������K

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_High;				// ������K

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_Weak_Crouch;		// ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_During_Crouch;	// ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_High_Crouch;		// �呫

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_Weak_Sky;			// �󒆏���

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_During_Sky;		// �󒆒���

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_High_Sky;			// �󒆑呫
};
