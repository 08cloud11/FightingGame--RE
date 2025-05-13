//--------------------------------------------------------------------
// �t�@�C���� �FTestBullet.h
// �T�v       �F�����蔻��e�X�g�p
// �쐬��     �F0231�{��
// �X�V���e   �F4/15�@�쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharactorBase.h"
#include "TestBullet.generated.h"

UCLASS()
class FIGHTING_API ATestBullet : public AActor
{
	GENERATED_BODY()
	
public:
	//�ړ�����
	enum MoveDirection
	{
		Move_Left,
		Move_Right,
		Move_Up,
		Move_Down
	};

public:	
	ATestBullet();

	virtual void Tick(float DeltaTime) override;

	void Set_movedir(MoveDirection value) { _movedir = value; }
	void Set_currentchara(CharaType charatype) { _curretchara = charatype; }

	CharaType Get_currentchara() const { return _curretchara; }

protected:
	virtual void BeginPlay() override;

private:
	void Move();

private:
	MoveDirection _movedir;

	UPROPERTY(EditAnywhere, Category = "Status")
	CharaType _curretchara = CharaType::None;
};
