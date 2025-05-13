//--------------------------------------------------------------------
// ファイル名 ：APlayerCharacter.cpp
// 概要       ：プレイヤーの基盤のクラス
// 作成者     ：0231本間
// 更新内容   ：4/15　作成
//--------------------------------------------------------------------

#include "Player2_Demo.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

void APlayer2_Demo::BeginPlay()
{
	Super::BeginPlay();

	_charatype = CharaType::charaA;
}

void APlayer2_Demo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().X != 0.0) {

		FVector pos = GetActorLocation();
		SetActorLocation(FVector(0.0, pos.Y, pos.Z));
	}

	Move();

	Jump(DeltaTime);

	if (_battack)
	{
		_punchTimer += DeltaTime;

		if (_punchTimer > 0.8)
		{
			_battack = false;
		}
	}
}

void APlayer2_Demo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// ジャンプ
		EnhancedInputComponent->BindAction(_InputActions["Jump"], ETriggerEvent::Started, this, &APlayer2_Demo::InputJump);

		// 移動
		EnhancedInputComponent->BindAction(_InputActions["Move"], ETriggerEvent::Triggered, this, &APlayer2_Demo::InputMove);

		// 攻撃
		EnhancedInputComponent->BindAction(_InputActions["Attack"], ETriggerEvent::Started, this, &APlayer2_Demo::AttackAction);
	}

}

void APlayer2_Demo::Move()
{
	if (!_bmove) return;

	FVector pos = GetActorLocation();

	switch (_moveDir)
	{
	case ACharactorBase::Move_Left:
		SetActorLocation(FVector(pos.X, pos.Y - 5.0, pos.Z));

		break;

	case ACharactorBase::Move_Right:
		SetActorLocation(FVector(pos.X, pos.Y + 5.0, pos.Z));

		break;
	}

	_bmove = false;
}

void APlayer2_Demo::PadMove(const FInputActionValue& axisvalue)
{
	//if (!_bmove) return;

	//FVector pos = GetActorLocation();

	//if (axisvalue. < 0.0)
	//{
	//	_moveDir = MoveDirection::Move_Left;
	//	//SetActorLocation(FVector(pos.X, pos.Y - 5.0, pos.Z));
	//}
	//else if (axisvalue.X > 0.0)
	//{
	//	_moveDir = MoveDirection::Move_Right;
	//	//SetActorLocation(FVector(pos.X, pos.Y + 5.0, pos.Z));
	//}

	//_bmove = false;
}

void APlayer2_Demo::Jump(float DeltaTime)
{
	if (!_bjump) return;

	_jumpTimer += DeltaTime;

	FVector newPos;
	FVector pPos = GetActorLocation();

	switch (_jumptype)
	{
	case ACharactorBase::Normal:
		newPos = FVector(pPos.X, pPos.Y, pPos.Z + 25.0);
		SetActorLocation(newPos);

		break;

	case ACharactorBase::Back:
		newPos = FVector(pPos.X, pPos.Y - 12.0, pPos.Z + 25.0);
		SetActorLocation(newPos);

		break;

	case ACharactorBase::Front:
		newPos = FVector(pPos.X, pPos.Y + 12.0, pPos.Z + 25.0);
		SetActorLocation(newPos);

		break;
	}

	if (_jumpTimer < 0.15) return;

	switch (_jumptype)
	{
	case ACharactorBase::Normal:
		newPos = FVector(pPos.X, pPos.Y, pPos.Z - 20.0);
		SetActorLocation(newPos);

		break;

	case ACharactorBase::Back:
		newPos = FVector(pPos.X, pPos.Y - 12.0, pPos.Z - 20.0);
		SetActorLocation(newPos);

		break;

	case ACharactorBase::Front:
		newPos = FVector(pPos.X, pPos.Y + 12.0, pPos.Z - 20.0);
		SetActorLocation(newPos);

		break;
	}

	if (newPos.Z > 90.0)return;

	newPos = FVector(newPos.X, newPos.Y, 90.0);
	SetActorLocation(newPos);

	_bjump = false;
	_jumpTimer = 0.0;
}

void APlayer2_Demo::AttackAction()
{
	if (_controller->IsInputKeyDown(FKey(EKeys::NumPadSeven))) {
		_atktype = AttackType::punch_weak;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::NumPadEight))) {
		_atktype = AttackType::punch_strong;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::NumPadNine))) {
		_atktype = AttackType::kick_weak;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::Add))) {
		_atktype = AttackType::kick_strong;
	}

	_battack = true;
	_punchTimer = 0.0;
}

void APlayer2_Demo::InputMove()
{
	FRotator rot;

	if (_controller->IsInputKeyDown(FKey(EKeys::NumPadFour))) {
		_moveDir = Move_Left;

		rot = FRotator(0.0, 180.0, 0.0);
		GetMesh()->SetWorldRotation(rot);
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::NumPadSix))) {
		_moveDir = Move_Right;
		rot = FRotator(0.0, 0.0, 0.0);
		GetMesh()->SetWorldRotation(rot);
	}

	_bmove = true;
}

void APlayer2_Demo::InputJump()
{
	if (_controller->IsInputKeyDown(FKey(EKeys::NumPadSeven))) {
		_jumptype = JumpType::Back;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::NumPadEight))) {
		_jumptype = JumpType::Normal;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::NumPadNine))) {
		_jumptype = JumpType::Front;
	}

	_bjump = true;
}