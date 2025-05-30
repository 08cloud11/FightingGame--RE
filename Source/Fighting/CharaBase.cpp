// Fill out your copyright notice in the Description page of Project Settings.

#include "CharaBase.h"
#include <valarray>
#include <cmath>

// �i����
// 
// �����ς�
// �E���Ⴊ��
// �E���ړ�
// �E�����W�����v
// �E�U���̔���
// �E�K�[�h
// �E�����蔻��
// �E�W�����v�i���W�����v�j
// �E�G������������
// �E�̂�����
// 
// ������
// �E�R�}���h�U��
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

	//// �U���̕ϐ�
	
	Punch_Weak = NewObject< AAttackBase >();			// �����R�p��
	Punch_During = NewObject< AAttackBase >();			// �������p��
	Punch_High = NewObject< AAttackBase >();			// ������p��
	Punch_Weak_Crouch = NewObject< AAttackBase >();		// ���Ⴊ�݃R�p��
	Punch_During_Crouch = NewObject< AAttackBase >();	// ���Ⴊ�ݒ��p��
	Punch_High_Crouch = NewObject< AAttackBase >();		// ���Ⴊ�ݑ�p��
	Punch_Weak_Sky = NewObject< AAttackBase >();		// �󒆃R�p��
	Punch_During_Sky = NewObject< AAttackBase >();		// �󒆒��p��
	Punch_High_Sky = NewObject< AAttackBase >();		// �󒆑�p��

	Kick_Weak = NewObject< AAttackBase >();				// ������K
	Kick_During = NewObject< AAttackBase >();			// ������K
	Kick_High = NewObject< AAttackBase >();				// ������K
	Kick_Weak_Crouch = NewObject< AAttackBase >();		// ����
	Kick_During_Crouch = NewObject< AAttackBase >();	// ����
	Kick_High_Crouch = NewObject< AAttackBase >();		// �呫
	Kick_Weak_Sky = NewObject< AAttackBase >();			// �󒆏���
	Kick_During_Sky = NewObject< AAttackBase >();		// �󒆒���
	Kick_High_Sky = NewObject< AAttackBase >();			// �󒆑呫
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
	// ���Ⴊ�ݓ��͒��ł��R�}���h���͂���t�ł���悤��
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

	// ������̓��͂�����Ă���ꍇ
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

	// �ړ��̏�����
	MoveDirection.Y = 0.0f;

}

void ACharaBase::Attack()
{
	// �U���{�^����������Ă��Ȃ��ꍇ�͏I��
	if (!_IsAttack) return;

	// �{�^����������Ă��āA�U���p�ϐ���AttackBase�������Ă��Ȃ����͎~�߂�
	if (Attacking == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Attacking is Null."));
		return;
	}

	// �^�C�}�[��i�߂�
	Attacking->AddAttackTimer();
	// UE_LOG(LogTemp, Log, TEXT("Timer : %i"), Attacking->GetAttackTimer());

	if (Attacking->IsOccurrenceFrame() && 
		!Attacking->IsContinuation())
	{
		// UE_LOG(LogTemp, Log, TEXT("AttackCollision IS Push"));

		// 
		Attacking->SetOccurrenceCollision("Delete");

		/*�U������̍쐬*/
		Attacking->SetStiffnessCollision();
		
		return; 
	}

	if (Attacking->IsContinuation() &&
		!Attacking->IsWholeFrame())
	{
		// UE_LOG(LogTemp, Log, TEXT("AttackCollision is Delete"));

		/*�U������̍폜�Ƃ����蔻��̑���*/
		Attacking->SetStiffnessCollision("Delete");

		Attacking->SetContinuationCollision();
		return;
	}

	if (!Attacking->IsWholeFrame()) return;

	// UE_LOG(LogTemp, Log, TEXT("Finish"));

	_IsAttack = false;

	_IsPunch_Weak = false;			// �����R�p��
	_IsPunch_During = false;			// �������p��
	_IsPunch_High = false;			// ������p��
	_IsPunch_Weak_Crouch = false;		// ���Ⴊ�݃R�p��
	_IsPunch_During_Crouch = false;	// ���Ⴊ�ݒ��p��
	_IsPunch_High_Crouch = false;		// ���Ⴊ�ݑ�p��
	_IsPunch_Weak_Sky = false;		// �󒆃R�p��
	_IsPunch_During_Sky = false;		// �󒆒��p��
	_IsPunch_High_Sky = false;		// �󒆑�p��

	_IsKick_Weak = false;				// ������K
	_IsKick_During = false;			// ������K
	_IsKick_High = false;				// ������K
	_IsKick_Weak_Crouch = false;		// ����
	_IsKick_During_Crouch = false;	// ����
	_IsKick_High_Crouch = false;		// �呫
	_IsKick_Weak_Sky = false;			// �󒆏���
	_IsKick_During_Sky = false;		// �󒆒���
	_IsKick_High_Sky = false;			// �󒆑呫

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

	// �G�ɃK�[�h������`����
	Cast<ACharaBase>(EnamyChara)->ShadySeam(PushButtom->GetGuardDistance());

	// ���͂��ꂽ�{�^�����U�����̃{�^���Ƃ��ēo�^����
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

	// �������Ȃ��Ȃ�K�[�h��Ԃɂ���
	if (Distance < _fShadySeam)
	{
		UE_LOG(LogTemp, Log, TEXT("Guord"));
		_IsGuord = true;
	}
}

void ACharaBase::SetAttackInfo(int Occurrence,
	int Continuation,	// ����
	int Stiffness,		// �d��
	int Stiffness_Hit,	// �q�b�g�d��
	int Stiffness_Fuar, // �K�[�h�d��
	int Damage,			// �_���[�W
	FString Property,	//  
	float Distance_Guard,				// �K�[�h����, 
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