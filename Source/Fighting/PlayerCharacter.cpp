

#include "PlayerCharacter.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	_charatype = CharaType::charaA;

	_controller = Cast<APlayerController>(Controller);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_controller->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(_defaultMappingContext, 0);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().X != 0.0) {

		FVector pos = GetActorLocation();
		SetActorLocation(FVector(0.0, pos.Y, pos.Z));
	}

	Move();

	Jump(DeltaTime);

	if (_bpunch)
	{
		_punchTimer += DeltaTime;

		if (_punchTimer > 0.8)
		{
			_bpunch = false;
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// ƒWƒƒƒ“ƒv
		EnhancedInputComponent->BindAction(_InputActions["Jump"], ETriggerEvent::Started, this, &APlayerCharacter::InputJump);

		// ˆÚ“®
		EnhancedInputComponent->BindAction(_InputActions["Move"], ETriggerEvent::Triggered, this, &APlayerCharacter::InputMove);

		// UŒ‚
		EnhancedInputComponent->BindAction(_InputActions["Attack"], ETriggerEvent::Started, this, &APlayerCharacter::AttackAction);
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

void APlayerCharacter::Move(float axisvalue)
{
	if (!_bmove) return;

	FVector pos = GetActorLocation();

	if (axisvalue < 0.0)
	{
		_moveDir = MoveDirection::Move_Left;
		//SetActorLocation(FVector(pos.X, pos.Y - 5.0, pos.Z));
	}
	else if (axisvalue > 0.0)
	{
		_moveDir = MoveDirection::Move_Right;
		//SetActorLocation(FVector(pos.X, pos.Y + 5.0, pos.Z));
	}

	_bmove = false;
}

void APlayerCharacter::Jump(float DeltaTime)
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

void APlayerCharacter::AttackAction()
{
	if (_controller->IsInputKeyDown(FKey(EKeys::One))) {
		_atktype = AttackType::punch_weak;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::Two))) {
		_atktype = AttackType::punch_strong;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::Three))) {
		_atktype = AttackType::kick_weak;
	}
	else if (_controller->IsInputKeyDown(FKey(EKeys::Four))) {
		_atktype = AttackType::kick_strong;
	}

	_bpunch = true;
	_punchTimer = 0.0;
}

void APlayerCharacter::InputMove()
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

void APlayerCharacter::InputJump()
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