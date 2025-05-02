//--------------------------------------------------------------------
// �t�@�C���� �FCharactorBase.cpp
// �T�v       �F�L�����N�^�[�̊�Ղ̃N���X
// �쐬��     �F0231�{��
// �X�V���e   �F4/15�@�쐬
//--------------------------------------------------------------------

#include "CharactorBase.h"
#include "PlayerCharacter.h"

ACharactorBase::ACharactorBase()
	: _jumpTimer(0.0)
	, _punchTimer(0.0)
	, _atktype(AttackType::None)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharactorBase::BeginPlay()
{
	Super::BeginPlay();

	Cast<UPrimitiveComponent>(GetRootComponent())->
		OnComponentBeginOverlap.AddDynamic(this, &ACharactorBase::OnOverlapBegin);
}

void ACharactorBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ATestBullet>(OtherActor))return;

	int thischaratype = int(_charatype);
	int othercharatype = Cast<ATestBullet>(OtherActor)->Get_currentchara();

	if (othercharatype == int(ATestBullet::CurretCharaType::None))return;
	if (thischaratype == othercharatype)return;

	this->_hp -= _attackpower;

	if (_hp <= 0)
	{
		Destroy();
	}
}

void ACharactorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


