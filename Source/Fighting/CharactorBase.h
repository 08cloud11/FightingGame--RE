//--------------------------------------------------------------------
// ファイル名 ：CharactorBase.h
// 概要       ：キャラクターの基盤のクラス
// 作成者     ：0231本間
// 更新内容   ：4/15　作成
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

//キャラの状態
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

	//移動方向
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

	// 引　数：UPrimitiveComponent*, OverlappedComp, 
	// 　　　　UPrimitiveComponent*, int32, bool, FHitResult
	// 戻り値：void
	// 処理内容：当たり判定
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

	// 引　数：なし
	// 戻り値：void
	// 処理内容：移動処理
	virtual void Move() {}
	virtual void Move(float) {};

	virtual void Jump(float DeltaTime){}

	// 引　数：なし
	// 戻り値：void
	// 処理内容：攻撃処理
	virtual void AttackAction() {}
	
	// 引　数：なし
	// 戻り値：void
	// 処理内容：仮想関数定義
	virtual void InputMove() {}

	virtual void InputJump(){}

protected:

	//移動ごとに進行方向を保管する。
	// アタックキーが押された時に判定
	MoveDirection _moveDir;

	//現在のキャラの行動
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

	bool _bmove = false;		//移動できるか
	bool _bjump = false;		//ジャンプできるか
	bool _bpunch = false;		//パンチできるか
};
