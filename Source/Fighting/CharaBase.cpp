// Fill out your copyright notice in the Description page of Project Settings.

#include "CharaBase.h"
#include <valarray>
#include <cmath>

// 進捗状況
// 
// 完成済み
// ・しゃがみ
// ・横移動
// ・垂直ジャンプ
// ・攻撃の発生
// ・ガード
// ・あたり判定
// ・ジャンプ（横ジャンプ）
// ・敵を向き続ける
// ・のけぞり
// 
// 未完成
// ・コマンド攻撃
// 

// Sets default values
ACharaBase::ACharaBase():
	_IsCrouch(false),
	_IsAttack(false),
	_IsJump(false),
	_IsGuord(false),
	_IsStiffness(false),
	_IsMoveing(false)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetHP(100);

	//// 攻撃の変数
	
	Punch_Weak = NewObject< AAttackBase >();			// 立ちコパン
	Punch_During = NewObject< AAttackBase >();			// 立ち中パン
	Punch_High = NewObject< AAttackBase >();			// 立ち大パン
	Punch_Weak_Crouch = NewObject< AAttackBase >();		// しゃがみコパン
	Punch_During_Crouch = NewObject< AAttackBase >();	// しゃがみ中パン
	Punch_High_Crouch = NewObject< AAttackBase >();		// しゃがみ大パン
	Punch_Weak_Sky = NewObject< AAttackBase >();		// 空中コパン
	Punch_During_Sky = NewObject< AAttackBase >();		// 空中中パン
	Punch_High_Sky = NewObject< AAttackBase >();		// 空中大パン

	Kick_Weak = NewObject< AAttackBase >();				// 立ち弱K
	Kick_During = NewObject< AAttackBase >();			// 立ち中K
	Kick_High = NewObject< AAttackBase >();				// 立ち大K
	Kick_Weak_Crouch = NewObject< AAttackBase >();		// 小足
	Kick_During_Crouch = NewObject< AAttackBase >();	// 中足
	Kick_High_Crouch = NewObject< AAttackBase >();		// 大足
	Kick_Weak_Sky = NewObject< AAttackBase >();			// 空中小足
	Kick_During_Sky = NewObject< AAttackBase >();		// 空中中足
	Kick_High_Sky = NewObject< AAttackBase >();			// 空中大足
}

// Called when the game starts or when spawned
void ACharaBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharaBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChangeState();

	stiffen();

	Move();

	Attack();

	Visual();
}

void ACharaBase::SetEnemy(APawn* EnemyPawn)
{
	EnamyChara = EnemyPawn;
}

// Called to bind functionality to input
void ACharaBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharaBase::SetHP(int _setHP)
{
	_HP = _setHP;
}

const int ACharaBase::GetHP()
{
	return _HP;
}

void ACharaBase::OverlapBoxCollision(APawn* Pawn)
{
	_IsStiffness = true;

	if (_IsGuord)
	{
		_Stiffness = Cast<ACharaBase>(EnamyChara)->GetAttackPointer()->GuardStiffness();

		return;
	}
	_Stiffness = Cast<ACharaBase>(EnamyChara)->GetAttackPointer()->HitStiffness();

	int AttackDamage = Cast<ACharaBase>(EnamyChara)->GetAttackPointer()->GetDamage();

	_HP -= AttackDamage;

	 UE_LOG(LogTemp, Log, TEXT("Test : %i"), _HP);
}

void ACharaBase::Jump()
{
	static int JumpNum = 1;

	static bool s_isJump = false;

	if (JumpNum  >= MaxJumpNum &&
		s_isJump == false)
	{
		JumpNum = 1;
		s_isJump = true;
	}
	else if 
	(JumpNum >= MaxJumpNum &&
	 s_isJump == true)
	{
		JumpNum = 1;
		s_isJump = false;
		_IsJump = false;

		return;
	}

	FVector pos = GetActorLocation();

	if (!s_isJump)
	{
		SetActorLocation(FVector(pos.X, pos.Y, pos.Z + c_JumpPower / (JumpNum)));
	}
	else
	{
		SetActorLocation(FVector(pos.X, pos.Y, pos.Z - (c_JumpPower / JumpNum)));
	}

	JumpNum++;
}

void ACharaBase::Jump(auto SideDirecition)
{
	static int JumpNum = 1;

	static bool s_isJump = false;

	if (JumpNum >= MaxJumpNum &&
		s_isJump == false)
	{
		JumpNum = 1;
		s_isJump = true;
	}
	else if
		(JumpNum >= MaxJumpNum &&
			s_isJump == true)
	{
		JumpNum = 1;
		s_isJump = false;
		_IsJump = false;

		return;
	}

	FVector pos = GetActorLocation();

	if (!s_isJump)
	{
		SetActorLocation(FVector(pos.X, pos.Y + (5.f  * SideDirecition), pos.Z + (c_JumpPower / (JumpNum) * 2 )));
	}
	else
	{
		SetActorLocation(FVector(pos.X , pos.Y + (5.f * SideDirecition), pos.Z - (c_JumpPower / JumpNum) * 2));
	}

	JumpNum++;


}

void ACharaBase::Visual()
{

}

void ACharaBase::SetAttackCollision(UBoxComponent* information, FString CollisionType , FString Part, FString strength, FString condition)
{
	AAttackBase* Search = SearchAttack(Part, strength, condition);

	//return;

	if (CollisionType == "Occurrence")
	{
		Search->SetOccurrenceCollision(information);
	}
	else if (CollisionType == "Stiffness")
	{
		Search->SetStiffnessCollision(information);
	}
	else if (CollisionType == "Continuation")
	{
		Search->SetContinuationCollision(information);
	}
}

void ACharaBase::SetMoveDirection(bool Move_Right, bool Move_Left, bool Move_Up, bool Move_Down)
{
	// しゃがみ入力中でもコマンド入力を受付できるように
	if (Move_Down) 
	{
		_IsCrouch = true;
	}

	if (Move_Up)
	{
		_IsJump = true; 
		return;
	}
		

	MoveDirection.Y = 1;
	 
	if (Move_Left)MoveDirection.Y = -1;
}

void ACharaBase::Move()
{
	static int Jumpst = 0;

	// 上方向の入力がされている場合
	if (_IsJump)
	{
		if (Jumpst == 0)
		{
			if (MoveDirection.Y != 0)
			{
				Jumpst = 1;
			}
			else
			{
				Jumpst = 2;
			}
		}

		switch (Jumpst)
		{
		case 1:
			Jump(MoveDirection.Y);
			break;
		case 2:
			Jump();
			break;
		}
		
		return;
	}
	else
	{
		Jumpst = 0;
	}

	if (_IsGuord ||
		_IsAttack ||
		_IsCrouch ||
		_IsStiffness)
	{
		MoveDirection.Y = 0.0f;
		_IsCrouch = false;
		return;
	}

	FVector pos = GetActorLocation();

	if (MoveDirection.Y > 0)
	{
		_IsMoveing = true;
	}
	else if (MoveDirection.Y == 0)
	{
		_IsMoveing = false;
	}

	SetActorLocation(FVector(pos.X , pos.Y + MoveDirection.Y * c_MoveSpeed, pos.Z));

	// 移動の初期化
	MoveDirection.Y = 0.0f;

}

void ACharaBase::Attack()
{
	// 攻撃ボタンが押されていない場合は終了
	if (!_IsAttack) return;

	// ボタンが押されていて、攻撃用変数にAttackBaseが入っていない時は止める
	if (Attacking == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Attacking is Null."));
		return;
	}

	// タイマーを進める
	Attacking->AddAttackTimer();
	// UE_LOG(LogTemp, Log, TEXT("Timer : %i"), Attacking->GetAttackTimer());

	if (Attacking->IsOccurrenceFrame() && 
		!Attacking->IsContinuation())
	{
		// UE_LOG(LogTemp, Log, TEXT("AttackCollision IS Push"));

		// 
		Attacking->SetOccurrenceCollision("Delete");

		/*攻撃判定の作成*/
		Attacking->SetStiffnessCollision();
		
		return; 
	}

	if (Attacking->IsContinuation() &&
		!Attacking->IsWholeFrame())
	{
		// UE_LOG(LogTemp, Log, TEXT("AttackCollision is Delete"));

		/*攻撃判定の削除とあたり判定の増加*/
		Attacking->SetStiffnessCollision("Delete");

		Attacking->SetContinuationCollision();
		return;
	}

	if (!Attacking->IsWholeFrame()) return;

	// UE_LOG(LogTemp, Log, TEXT("Finish"));

	_IsAttack = false;

	_IsPunch_Weak = false;			// 立ちコパン
	_IsPunch_During = false;			// 立ち中パン
	_IsPunch_High = false;			// 立ち大パン
	_IsPunch_Weak_Crouch = false;		// しゃがみコパン
	_IsPunch_During_Crouch = false;	// しゃがみ中パン
	_IsPunch_High_Crouch = false;		// しゃがみ大パン
	_IsPunch_Weak_Sky = false;		// 空中コパン
	_IsPunch_During_Sky = false;		// 空中中パン
	_IsPunch_High_Sky = false;		// 空中大パン

	_IsKick_Weak = false;				// 立ち弱K
	_IsKick_During = false;			// 立ち中K
	_IsKick_High = false;				// 立ち大K
	_IsKick_Weak_Crouch = false;		// 小足
	_IsKick_During_Crouch = false;	// 中足
	_IsKick_High_Crouch = false;		// 大足
	_IsKick_Weak_Sky = false;			// 空中小足
	_IsKick_During_Sky = false;		// 空中中足
	_IsKick_High_Sky = false;			// 空中大足

	Attacking->ResetAttackTimer();
	Attacking = nullptr;
}

void ACharaBase::PushAttackButtom(FString Part, FString strength)
{
	if (_IsAttack == true) return;

	AAttackBase* PushButtom = nullptr;

	if (_IsCrouch)
	{
		PushButtom = SearchAttack(Part, strength, "Crouch");
	}
	else if (_IsJump)
	{
		PushButtom = SearchAttack(Part, strength, "Sky");
	}
	else
	{
		PushButtom = SearchAttack(Part, strength, "Stand");
	}

	_IsAttack = true;

	// 敵にガード距離を伝える
	Cast<ACharaBase>(EnamyChara)->ShadySeam(PushButtom->GetGuardDistance());

	// 入力されたボタンを攻撃中のボタンとして登録する
	Attacking = PushButtom;

	// 
	Attacking->SetOccurrenceCollision();

}

AAttackBase* ACharaBase::NowAttackInfo()
{
	if(Attacking == nullptr) return nullptr;

	return Attacking;
}

void ACharaBase::ChangeState()
{
	
}

AAttackBase* ACharaBase::SearchAttack(FString Part, FString strength, FString condition)
{
	if (Part != "Punch" &&
		Part != "Kick") 
	{
		UE_LOG(LogTemp, Log, TEXT("Part is not on the Library"));
		return nullptr;
	}

	if (strength != "Weak" &&
		strength != "During" &&
		strength != "High")
	{
		UE_LOG(LogTemp, Log, TEXT("strength is not on the Library"));
		return nullptr;
	}

	if (condition != "Stand" &&
		condition != "Crouch" &&
		condition != "Sky")
	{
		UE_LOG(LogTemp, Log, TEXT("condition is not on the Library"));
		return nullptr;
	}

	AAttackBase* NowPushAttack = nullptr;

	if (Part == "Punch")
	{
		if (strength == "Weak")
		{
			if (condition == "Stand")
			{
				NowPushAttack = Punch_Weak;
				_IsPunch_Weak = true;
			}
			else if (condition == "Crouch")
			{
				NowPushAttack = Punch_Weak_Crouch;
				_IsPunch_Weak_Crouch = true;
			}
			else if (condition == "Sky")
			{
				NowPushAttack = Punch_Weak_Sky;
				_IsPunch_Weak_Sky = true;
			}
		}
		else if(strength == "During")
		{
			if (condition == "Stand")
			{
				NowPushAttack = Punch_During;
				_IsPunch_During = true;
			}
			else if (condition == "Crouch")
			{
				NowPushAttack = Punch_During_Crouch;
				_IsPunch_During_Crouch = true;
			}
			else if (condition == "Sky")
			{
				NowPushAttack = Punch_During_Sky;
				_IsPunch_During_Sky = true;
			}
		}
		else if (strength == "High")
		{
			if (condition == "Stand")
			{
				NowPushAttack = Punch_High;
				_IsPunch_High = true;
			}
			else if (condition == "Crouch")
			{
				NowPushAttack = Punch_High_Crouch;
				_IsPunch_High_Crouch = true;
			}
			else if (condition == "Sky")
			{
				NowPushAttack = Punch_High_Sky;
				_IsPunch_High_Sky = true;
			}
		}

	}
	else if(Part == "Kick")
	{
		if (strength == "Weak")
		{
			if (condition == "Stand")
			{
				NowPushAttack = Kick_Weak;
				_IsKick_Weak = true;
			}
			else if (condition == "Crouch")
			{
				NowPushAttack = Kick_Weak_Crouch;
				_IsKick_Weak_Crouch = true;
			}
			else if (condition == "Sky")
			{
				NowPushAttack = Kick_Weak_Sky;
				_IsKick_Weak_Sky = true;
			}
		}
		else if (strength == "During")
		{
			if (condition == "Stand")
			{
				NowPushAttack = Kick_During;
				_IsKick_During = true;
			}
			else if (condition == "Crouch")
			{
				NowPushAttack = Kick_During_Crouch;
				_IsKick_During_Crouch = true;
			}
			else if (condition == "Sky")
			{
				NowPushAttack = Kick_During_Sky;
				_IsKick_During_Sky = true;
			}
		}
		else if (strength == "High")
		{
			if (condition == "Stand")
			{
				NowPushAttack = Kick_High;
				_IsKick_High = true;
			}
			else if (condition == "Crouch")
			{
				NowPushAttack = Kick_High_Crouch;
				_IsKick_High_Crouch = true;
			}
			else if (condition == "Sky")
			{
				NowPushAttack = Kick_High_Sky;
				_IsKick_High_Sky = true;
			}
		}

	}

	return NowPushAttack;
}

void ACharaBase::Crouch()
{
	if (!_IsCrouch) return;


}

void ACharaBase::ShadySeam(float _fShadySeam)
{
	FVector pos = GetActorLocation();
	FVector Enemypos = EnamyChara->GetActorLocation();

	float Distance;

	if (pos.Y > Enemypos.Y)
	{
		Distance = pos.Y - Enemypos.Y;
	}
	else
	{
		Distance = Enemypos.Y - pos.Y;
	}

	// 距離いないならガード状態にする
	if (Distance < _fShadySeam)
	{
		UE_LOG(LogTemp, Log, TEXT("Guord"));
		_IsGuord = true;
	}
}

void ACharaBase::SetAttackInfo(int Occurrence,
	int Continuation,	// 持続
	int Stiffness,		// 硬直
	int Stiffness_Hit,	// ヒット硬直
	int Stiffness_Fuar, // ガード硬直
	int Damage,			// ダメージ
	FString Property,	//  
	float Distance_Guard,				// ガード距離, 
	FString Part,
	FString strength,
	FString condition)
{
	AAttackBase* Search = SearchAttack(Part, strength, condition);

	Search->SetAttackInfomation(Occurrence ,Continuation, Stiffness, Stiffness_Hit, Stiffness_Fuar, Damage, Property, Distance_Guard);
}

void ACharaBase::stiffen()
{
	if (!_IsStiffness) return;

	--_Stiffness;

	if (_Stiffness == 0)
	{
		_IsStiffness = false;
	}
}

bool ACharaBase::GetJump()
{
	return _IsJump;
}

bool ACharaBase::GetMove()
{
	return _IsMoveing;
}

AAttackBase* ACharaBase::GetAttackPointer()
{
	return Attacking;
}

bool ACharaBase::GetCrouch()
{
	return _IsCrouch;
}