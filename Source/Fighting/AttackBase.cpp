// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackBase.h"

// Sets default values
AAttackBase::AAttackBase():AttackTimer(0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAttackBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAttackBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAttackBase::InputAttack()
{

}

// �U���p�̃^�C�}�[�𓮂���
void AAttackBase::AddAttackTimer()
{
	++AttackTimer;
}


// �U���̃t���[�����擾����
// �����t���[��
const bool AAttackBase::IsOccurrenceFrame()
{
	return AttackTimer > Occurrence ? true : false;
}

// ����
const bool AAttackBase::IsContinuation()
{
	return AttackTimer > Occurrence + Continuation ? true : false;
}

// �d��
const bool AAttackBase::IsWholeFrame()
{
	return AttackTimer > Occurrence + Continuation  + Stiffness ? true : false;
}

// �A�^�b�N�^�C�}�[�����Z�b�g����
void AAttackBase::ResetAttackTimer()
{
	AttackTimer = 0;
}

// �A�^�b�N�^�C�}�[���擾����
int  AAttackBase::GetAttackTimer()
{
	return AttackTimer;
}

// �R���W������ݒ肷��
// ����
void AAttackBase::SetOccurrenceCollision(UBoxComponent* UBoxCollision)
{
	OccurrenceCollision = UBoxCollision;

	// OccurrenceCollision->SetCollisionEnabled();
}

// �U������
void AAttackBase::SetStiffnessCollision(UBoxComponent* UBoxCollision)
{
	StiffnessCollision = UBoxCollision;

	// OccurrenceCollision->SetCollisionEnabled();
}

// �d��������
void AAttackBase::SetContinuationCollision(UBoxComponent* UBoxCollision)
{
	ContinuationCollsion = UBoxCollision;

	// OccurrenceCollision->SetCollisionEnabled();
}

// �K�[�h�����̎擾
float AAttackBase::GetGuardDistance()
{
	return Distance_Guard;
}

void AAttackBase::SetAttackInfomation(int _Occurrence,
	int _Continuation,	// ����
	int _Stiffness,		// �d��
	int _Stiffness_Hit,	// �q�b�g�d��
	int _Stiffness_Fuar, // �K�[�h�d��
	int _Damage,			// �_���[�W
	FString _Property,	//  
	float _Distance_Guard				// �K�[�h����, 
)
{
	Occurrence = _Occurrence;

	Continuation = _Continuation;

	Stiffness = _Stiffness;

	Stiffness_Hit = _Stiffness_Hit;

	Stiffness_Fuard = _Stiffness_Fuar;

	Damage = _Damage;

	Property = _Property;

	Distance_Guard = _Distance_Guard;
}

// �_���[�W���擾����
int AAttackBase::GetDamage()
{
	return Damage;
}

void AAttackBase::SetOccurrenceCollision()
{
	//UE_LOG(LogTemp, Log, TEXT("QueryOnly : OccurrenceCollision is %x"), OccurrenceCollision);
	
	if (OccurrenceCollision == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("QueryOnly : OccurrenceCollision is null"));

		return;
	}

	OccurrenceCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AAttackBase::SetOccurrenceCollision(FString Delete)
{
	//UE_LOG(LogTemp, Log, TEXT("NoCollision : OccurrenceCollision is %x"), OccurrenceCollision);

	if (OccurrenceCollision == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("NoCollision : OccurrenceCollision is null"));

		return;
	}

	OccurrenceCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAttackBase::SetStiffnessCollision()
{
	//UE_LOG(LogTemp, Log, TEXT("QueryOnly : StiffnessCollision is %x"), StiffnessCollision);

	if (StiffnessCollision == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("QueryOnly : StiffnessCollision is null"));

		return;
	}

	StiffnessCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AAttackBase::SetStiffnessCollision(FString Delete)
{
	//UE_LOG(LogTemp, Log, TEXT("NoCollision : StiffnessCollision is %x"), StiffnessCollision);

	if (StiffnessCollision == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("NoCollision : StiffnessCollision is null"));

		return;
	}

	StiffnessCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAttackBase::SetContinuationCollision()
{
	//UE_LOG(LogTemp, Log, TEXT("QueryOnly : ContinuationCollision is %x"), ContinuationCollsion);

	if (ContinuationCollsion == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("QueryOnly : ContinuationCollision is null"));

		return;
	}

	ContinuationCollsion->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AAttackBase::SetContinuationCollision(FString Delete)
{
	// UE_LOG(LogTemp, Log, TEXT("NoCollision : ContinuationCollision is %x"), ContinuationCollsion);

	if (ContinuationCollsion == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("NoCollision : ContinuationCollsion is null"));

		return;
	}

	ContinuationCollsion->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

int AAttackBase::HitStiffness()
{
	return Stiffness_Hit;
}

int AAttackBase::GuardStiffness()
{
	return Stiffness_Fuard;
}

