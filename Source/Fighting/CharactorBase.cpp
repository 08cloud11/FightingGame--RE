//--------------------------------------------------------------------
// ファイル名 ：CharactorBase.cpp
// 概要       ：キャラクターの基盤のクラス
// 作成者     ：0231本間
// 更新内容   ：4/15　作成
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
	if (Cast<ACharactorBase>(OtherActor)) {
		UE_LOG(LogTemp, Log, TEXT("overlap : this :%d : other : %d"), int(this->Get_charatype()), 
			int(Cast<ACharactorBase>(OtherActor)->Get_charatype()));
	}
	else if (Cast<ATestBullet>(OtherActor)) {
		UE_LOG(LogTemp, Log, TEXT("overlap : this :%d : other : %d"), int(this->Get_charatype()),
			int(Cast<ATestBullet>(OtherActor)->Get_currentchara()));
	}

	if (_bdamaged) return;	//ダメージリアクション中
	if (!Cast<ATestBullet>(OtherActor))return; //当たったアクターが指定のものではない
	if (Cast<ATestBullet>(OtherActor)->Get_currentchara() == CharaType::None)return; //当たったアクターの攻撃の種別が指定されていない
	if (Cast<ATestBullet>(OtherActor)->Get_currentchara() == _charatype)return; //自分自身

	this->_hp -= _attackpower;
	//OtherActor->Destroy();

	GetMesh()->SetOverlayMaterial(_overlaymat);

	if (_hp <= 0){
		_bdead = true;
	}
	else {
		_bdamaged = true;
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

	//小刻みに震える処理
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
		GetMesh()->SetOverlayMaterial(nullptr);
		_bdamaged = false;
		_damagedflame = 0;
	}
}
