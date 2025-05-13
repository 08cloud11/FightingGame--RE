//--------------------------------------------------------------------
// ファイル名 ：TestBullet.h
// 概要       ：当たり判定テスト用
// 作成者     ：0231本間
// 更新内容   ：4/15　作成
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
	//移動方向
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
