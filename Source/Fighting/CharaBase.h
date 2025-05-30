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

	// いましている攻撃の情報を伝える
	AAttackBase* NowAttackInfo();

// ブループリント系の関数
public:
	// HPの設定
	UFUNCTION(BlueprintCallable)
	void SetHP(int _setHP);

	// HPの取得
	UFUNCTION(BlueprintCallable)
	const int GetHP();

	UFUNCTION(BlueprintCallable)
	void SetEnemy(APawn* EnemyPawn);

	// あたり判定系の処理
	UFUNCTION(BlueprintCallable)
	void OverlapBoxCollision(APawn* Pawn);

	// 攻撃系のあたり判定情報の設定
	UFUNCTION(BlueprintCallable)
	void SetAttackCollision(UBoxComponent* information, FString CollisionType, FString Part, FString strength, FString condition);

	// 攻撃系の情報をセットする
	UFUNCTION(BlueprintCallable)
	void SetAttackInfo(int Occurrence, 
	int Continuation,	// 持続
	int Stiffness,		// 硬直
	int Stiffness_Hit,	// ヒット硬直
	int Stiffness_Fuar, // ガード硬直
	int Damage,			// ダメージ
	FString Property,	//  
	float Distance_Guard,				// ガード距離, 
	FString Part, 
	FString strength, 
	FString condition);

	// 移動系のボタンが押されたときに呼ばれる
	UFUNCTION(BlueprintCallable)
	void SetMoveDirection(bool Move_Right, bool Move_Left, bool Move_Up, bool Move_Down);

	// アタック系のボタンが呼ばれたときに呼び出される
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

	// 横方向の入力がある時のジャンプ
	void Jump(auto SideDirecition);

	// 垂直ジャンプ
	void Jump();

	// 攻撃系
	void Attack();

	// しゃがみ
	void Crouch();

	// ステータスを変更する
	void ChangeState();

	// 見た目の変更
	void Visual();

	// 攻撃の検索
	AAttackBase* SearchAttack(FString Part, FString strength, FString condition);

	void stiffen();

private:
	APawn* EnamyChara;

	// 攻撃の変数
	TObjectPtr< AAttackBase > Punch_Weak;			// 立ちコパン
	TObjectPtr< AAttackBase > Punch_During;			// 立ち中パン
	TObjectPtr< AAttackBase > Punch_High;			// 立ち大パン
	TObjectPtr< AAttackBase > Punch_Weak_Crouch;		// しゃがみコパン
	TObjectPtr< AAttackBase > Punch_During_Crouch;	// しゃがみ中パン
	TObjectPtr< AAttackBase > Punch_High_Crouch;		// しゃがみ大パン
	TObjectPtr< AAttackBase > Punch_Weak_Sky;		// 空中コパン
	TObjectPtr< AAttackBase > Punch_During_Sky;		// 空中中パン
	TObjectPtr< AAttackBase > Punch_High_Sky;		// 空中大パン

	TObjectPtr< AAttackBase > Kick_Weak;				// 立ち弱K
	TObjectPtr< AAttackBase > Kick_During;			// 立ち中K
	TObjectPtr< AAttackBase > Kick_High;				// 立ち大K
	TObjectPtr< AAttackBase > Kick_Weak_Crouch;		// 小足
	TObjectPtr< AAttackBase > Kick_During_Crouch;	// 中足
	TObjectPtr< AAttackBase > Kick_High_Crouch;		// 大足
	TObjectPtr< AAttackBase > Kick_Weak_Sky;			// 空中小足
	TObjectPtr< AAttackBase > Kick_During_Sky;		// 空中中足
	TObjectPtr< AAttackBase > Kick_High_Sky;			// 空中大足

	AAttackBase* Attacking;				// 攻撃中の変数

	int _HP;				// HP

	const float c_MoveSpeed = 30.f;	// 移動速度
	const float c_JumpPower = 30.f;

	const int MaxJumpNum = 60;
	const int SinMax = 180;

	int _Stiffness;		// 硬直フレーム
	bool _IsStiffness;

	bool _IsGuord;			// ガードするか
	bool _IsJump;		// ジャンプしているか
	bool _IsAttack;		// 攻撃しているか
	bool _IsCrouch;		// しゃがんでいるか
	bool _IsRecive;		// 攻撃を受けているか
	bool _IsMoveing;

	FVector2D MoveDirection;

	// のち削除予定
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_Weak;			// 立ちコパン

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_During;			// 立ち中パン

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_High;			// 立ち大パン

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_Weak_Crouch;		// しゃがみコパン

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_During_Crouch;	// しゃがみ中パン

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_High_Crouch;		// しゃがみ大パン

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_Weak_Sky;		// 空中コパン

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_During_Sky;		// 空中中パン

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsPunch_High_Sky;		// 空中大パン


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_Weak;				// 立ち弱K

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_During;			// 立ち中K

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_High;				// 立ち大K

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_Weak_Crouch;		// 小足

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_During_Crouch;	// 中足

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_High_Crouch;		// 大足

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_Weak_Sky;			// 空中小足

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_During_Sky;		// 空中中足

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsKick_High_Sky;			// 空中大足
};
