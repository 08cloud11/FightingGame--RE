//--------------------------------------------------------------------
// �t�@�C���� �FCharactorBase.cpp
// �T�v       �F�L�����N�^�[�̊�Ղ̃N���X
// �쐬��     �F0231�{��
// �X�V���e   �F4/15�@�쐬
//--------------------------------------------------------------------

#include "CharactorBase.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "TestBullet.h"

ACharactorBase::ACharactorBase()
	: _jumpTimer(0.0)
	, _punchTimer(0.0)
	, _attackedflame(0)
	, _damagedflame(0)
	, _atktype(AttackType::None)
{
	PrimaryActorTick.bCanEverTick = true;

	//�F�ω��p�̏����i�r���j
	/*USkeletalMeshComponent* mesh = this->GetMesh();

	if (IsValid(mesh)) {

		UE_LOG(LogTemp, Log, TEXT("ACharactorBase : ACharactorBase()"));
		for (auto mat : mesh->GetMaterials())
		{
			_mats[i] = mat->CreateDynamicMaterialInstance(i);
		}
	}*/
}

void ACharactorBase::BeginPlay()
{
	Super::BeginPlay();

	Cast<UPrimitiveComponent>(GetRootComponent())->
		OnComponentBeginOverlap.AddDynamic(this, &ACharactorBase::OnOverlapBegin);

	_mpcinstance = GetWorld()->GetParameterCollectionInstance(_mpc);
	
	UMaterialInterface* player_bodymat = this->GetMesh()->GetMaterialByName(TEXT("Body"));

	/*UMaterialInstanceDynamic* bodymat_dynamic =*/
}

void ACharactorBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (_bdamaged) return;	//�_���[�W���A�N�V������
	if (!Cast<ATestBullet>(OtherActor))return; //���������A�N�^�[���w��̂��̂ł͂Ȃ�
	if (Cast<ATestBullet>(OtherActor)->Get_currentchara() == CharaType::None)return; //���������A�N�^�[�̍U���̎�ʂ��w�肳��Ă��Ȃ�
	if (Cast<ATestBullet>(OtherActor)->Get_currentchara() == _charatype)return; //�������g

	this->_hp -= _attackpower;
	OtherActor->Destroy();

	_mpcinstance->SetVectorParameterValue(FName("AddVector"), FColor(255, 255, 255, 255));
	/*_mpcinstance-> (FName("AddVector"))*/
	_bdamaged = true;

	if (_hp <= 0)
	{
		Destroy();
	}
}

void ACharactorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_bdamaged) Damaged();
}

void ACharactorBase::Damaged()
{
	FVector pos = GetActorLocation();

	//�F�ω��p�̏����i�r���j
	/*for (int i = 0; i < 3; i++)
	{
		_mats[i]->SetVectorParameterValue(TEXT("Value"), FVector(1.0, 0.2, 0.2));
	}*/
	//_mats[0]->SetVectorParameterValue(TEXT("Value"), FVector(1.0, 0.2, 0.2));

	//�����݂ɐk���鏈��
	switch (_damagedflame % 2)
	{
	case 0:
		SetActorLocation(FVector(pos.X, pos.Y + 5.0, pos.Z));

		break;

	case 1:
		SetActorLocation(FVector(pos.X, pos.Y - 5.0, pos.Z));

		break;
	}

	_damagedflame++;

	if (_damagedflame > 12)
	{
		_bdamaged = false;
		_damagedflame = 0;
	}
}
