//--------------------------------------------------------------------
// ファイル名 ：PlayerCharacter.cpp
// 概要       ：プレイヤーの基盤のクラス
// 作成者     ：0231本間
// 更新内容   ：4/15　作成
//--------------------------------------------------------------------

#include "PlayerCharacter.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Player2_Demo.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	if (_bdead)return;

	Super::Tick(DeltaTime);

	//上下左右の移動のみのため、奥行きの固定
	if (GetActorLocation().X != 0.0) {

		FVector pos = GetActorLocation();
		SetActorLocation(FVector(0.0, pos.Y, pos.Z));
	}

	Move();

	Jump(DeltaTime);

	//攻撃ボタンが押されている
	if (_nextatkstate != AttackType::None)
	{
		_attackedflame++;

		if (_attackedflame > 40)
		{
			_battack = true;
			_punchTimer = 0.0;

			_atktype = _nextatkstate;
			_nextatkstate = AttackType::None;

			_attackedflame = 0;
			_comandvals = 0;
		}
		//コマンド技(波動拳)
		else if (_comandvals == 3)
		{
			_battack = true;
			_punchTimer = 0.0;
			_atktype = AttackType::hadouken;
			_nextatkstate = AttackType::None;

			_attackedflame = 0;
			_comandvals = 0;
		}
	}	

	if (_battack)
	{
		_punchTimer += DeltaTime;

		if (_punchTimer > 0.8)
		{
			_battack = false;
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// ジャンプ
		EnhancedInputComponent->BindAction(_InputActions["Jump"], ETriggerEvent::Started, this, &APlayerCharacter::InputJump);

		// 移動
		EnhancedInputComponent->BindAction(_InputActions["Move"], ETriggerEvent::Triggered, this, &APlayerCharacter::InputMove);

		// 移動（ゲームパッド）
		EnhancedInputComponent->BindAction(_InputActions["PadMove"], ETriggerEvent::Triggered, this, &APlayerCharacter::PadMove);

		// 攻撃
		EnhancedInputComponent->BindAction(_InputActions["Attack"], ETriggerEvent::Started, this, &APlayerCharacter::AttackAction);

		// ダメージ
		EnhancedInputComponent->BindAction(_InputActions["Damage"], ETriggerEvent::Started, this, &APlayerCharacter::Damage);
	}

}

void APlayerCharacter::SetUpController(APlayerController* val)
{
	_controller = val;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_controller->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(_defaultMappingContext, 0);
	}

	if (_controller)
	{
		_controller->bShowMouseCursor = true; // カーソルを表示
	}
}

void APlayerCharacter::Move()
{
	if (!_bmove) return;

	FVector pos = GetActorLocation();

	switch (_moveDir)
	{
	case APlayerCharacter::Move_Left:
		SetActorLocation(FVector(pos.X, pos.Y - 5.0, pos.Z));

		break;

	case APlayerCharacter::Move_Right:
		SetActorLocation(FVector(pos.X, pos.Y + 5.0, pos.Z));

		break;
	}

	_bmove = false;
}

void APlayerCharacter::PadMove(const FInputActionValue& axisvalue)
{
	if (_bdead)return;

	FVector pos = GetActorLocation();

	FVector2D value = axisvalue.Get<FVector2D>();

	if (value.X < 0.0 && value.X < -0.5)
	{
		_moveDir = Move_Left;
		SetActorLocation(FVector(pos.X, pos.Y - 5.0, pos.Z));
		_bmove = true;
	}
	else if (value.X > 0.0 && value.X > 0.5)
	{
		_moveDir = Move_Right;
		SetActorLocation(FVector(pos.X, pos.Y + 5.0, pos.Z));
		_bmove = true;
	}	

	_bmove = false;
}

void APlayerCharacter::Jump(float DeltaTime)
{
	if (_bdead)return;
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

void APlayerCharacter::AttackAction()
{
	if (_bdead)return;

	//弱パンチ
	if (_controller->IsInputKeyDown(FKey(EKeys::One))
		|| _controller->IsInputKeyDown(FKey(EKeys::Gamepad_FaceButton_Bottom))) {
		_nextatkstate = AttackType::punch_weak;

		if (_comandvals == 0) _comandvals++;
	}
	//強パンチ
	else if (_controller->IsInputKeyDown(FKey(EKeys::Two))
		|| _controller->IsInputKeyDown(FKey(EKeys::Gamepad_FaceButton_Right))) {
		_nextatkstate = AttackType::punch_strong;

		if (_comandvals == 1) _comandvals++;
	}
	//弱キック
	else if (_controller->IsInputKeyDown(FKey(EKeys::Three))
		|| _controller->IsInputKeyDown(FKey(EKeys::Gamepad_FaceButton_Top))) {
		_nextatkstate = AttackType::kick_weak;

		if (_comandvals == 2) _comandvals++;
	}
	//強キック
	else if (_controller->IsInputKeyDown(FKey(EKeys::Four))
		|| _controller->IsInputKeyDown(FKey(EKeys::Gamepad_FaceButton_Left))) {
		_nextatkstate = AttackType::kick_strong;
	}
}

void APlayerCharacter::Damage()
{
	if (_bdamaged) return;	//ダメージリアクション中

	this->_hp -= _attackpower;

	_bdamaged = true;

	if (_hp <= 0)
	{
		Destroy();
	}
}

void APlayerCharacter::InputMove()
{
	if (_bdead)return;

	if (!IsValid(_controller))return;

	FRotator rot;

	if (_controller->IsInputKeyDown(FKey(EKeys::A))) {
		_moveDir = Move_Left;

		rot = FRotator(0.0, 180.0, 0.0);
		GetMesh()->SetWorldRotation(rot);
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::D))) {
		_moveDir = Move_Right;
		rot = FRotator(0.0, 0.0, 0.0);
		GetMesh()->SetWorldRotation(rot);
	}

	_bmove = true;
}

void APlayerCharacter::InputJump()
{
	if (_bdead)return;

	if (!IsValid(_controller))return;

	if (_controller->IsInputKeyDown(FKey(EKeys::Z))) {
		_jumptype = JumpType::Back;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::X))) {
		_jumptype = JumpType::Normal;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::C))) {
		_jumptype = JumpType::Front;
	}

	_bjump = true;
}