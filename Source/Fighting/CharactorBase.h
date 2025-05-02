//--------------------------------------------------------------------
// �t�@�C���� �FCharactorBase.h
// �T�v       �F�L�����N�^�[�̊�Ղ̃N���X
// �쐬��     �F0231�{��
// �X�V���e   �F4/15�@�쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestBullet.h"
#include "AttackComponent.h"
#include "CharactorBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

//�L�����̏��
UENUM(BlueprintType)
enum class CharaState : uint8
{
	State_Idle UMETA(DisplayName = "None"),
	State_Move UMETA(DisplayName = "Move"),
	State_Jump UMETA(DisplayName = "Jump"),
	State_Attack UMETA(DisplayName = "Attack")
};

UENUM(BlueprintType)
enum class CharaType :uint8
{
	charaA UMETA(DisplayName = "A"),
	charaB UMETA(DisplayName = "B"),
};

UENUM(BlueprintType)
enum class AttackType : uint8
{
	punch_weak UMETA(DisplayName = "Punch_Weak"),
	punch_medium UMETA(DisplayName = "Punch_Medium"),
	punch_strong UMETA(DisplayName = "Punch_Strong"),
	kick_weak UMETA(DisplayName = "Kick_Weak"),
	kick_medium UMETA(DisplayName = "Kick_Medium"),
	kick_strong UMETA(DisplayName = "Kick_Strong"),
	None UMETA(DisplayName = "None"),
};

UCLASS()
class FIGHTING_API ACharactorBase : public ACharacter
{
	GENERATED_BODY()

protected:

	//�ړ�����
	enum MoveDirection
	{
		Move_Left,
		Move_Right,
		Move_Up,
		Move_Down
	};

	enum JumpType
	{
		Normal,
		Back,
		Front
	};

public:
	ACharactorBase();

	// ���@���FUPrimitiveComponent*, OverlappedComp, 
	// �@�@�@�@UPrimitiveComponent*, int32, bool, FHitResult
	// �߂�l�Fvoid
	// �������e�F�����蔻��
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override {
		Super::SetupPlayerInputComponent(PlayerInputComponent);
	};

	CharaType Get_charatype() const { return _charatype; }

	UFUNCTION(BlueprintCallable)
	AttackType Get_atktype() const { return _atktype; }

	int Get_moveDir() const { return int(_moveDir); }

	UFUNCTION(BlueprintCallable)
	int Get_hp() const { return _hp; }

	UFUNCTION(BlueprintCallable)
	bool Get_bmove() const { return _bmove; }

	UFUNCTION(BlueprintCallable)
	bool Get_bjump() const { return _bjump; }

	UFUNCTION(BlueprintCallable)
	bool Get_bpunch() const { return _bpunch; }

	void Set_atktype(AttackType value) { _atktype = value; }

protected:
	virtual void BeginPlay() override;

	// ���@���F�Ȃ�
	// �߂�l�Fvoid
	// �������e�F�ړ�����
	virtual void Move() {}
	virtual void Move(float) {};

	virtual void Jump(float DeltaTime){}

	// ���@���F�Ȃ�
	// �߂�l�Fvoid
	// �������e�F�U������
	virtual void AttackAction() {}
	
	// ���@���F�Ȃ�
	// �߂�l�Fvoid
	// �������e�F���z�֐���`
	virtual void InputMove() {}

	virtual void InputJump(){}

protected:

	//�ړ����Ƃɐi�s������ۊǂ���B
	// �A�^�b�N�L�[�������ꂽ���ɔ���
	MoveDirection _moveDir;

	//���݂̃L�����̍s��
	CharaState _status;

	UPROPERTY(EditAnywhere, Category = "CharaType")
	CharaType _charatype;

	JumpType _jumptype;

	AttackType _atktype;

	double _jumpTimer;
	double _punchTimer;

	int _hp = 3000;
	const int _max_hp = 3000;

	UPROPERTY(EditAnywhere, Category = "Status")
	int _attackpower = 500;

	bool _bmove = false;		//�ړ��ł��邩
	bool _bjump = false;		//�W�����v�ł��邩
	bool _bpunch = false;		//�p���`�ł��邩
};
