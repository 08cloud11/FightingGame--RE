// ---------------------------------------------------------------------
// 
// 
// 
// ---------------------------------------------------------------------
#pragma once

#include "CharactorBase.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FightingGameMode.generated.h"

UCLASS()
class FIGHTING_API AFightingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFightingGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	static void GetAllConnectionDevice(TArray<FInputDeviceId>& OutInputDevices);

private:
	UPROPERTY()
	int _ControllerID;		// コントローラー
	int _PlayerNum;			// 操作可能なプレイヤー数

	/*UPROPERTY()
	TArray<AMyCharacter*> PlayerActor;*/

	/*UPROPERTY()
	TArray<AMyPlayerController*> PlayerContoloer;*/

private:
	// コントローラーとプレイヤーの接続をする関数

	// プレイヤーを生成する
	void _CreateToPlayer();

	// プレイヤーのHPを取得する
	template<typename PlayerType >void _SetPlayerHP(PlayerType* Player);

	// 勝敗判定

	// 時間計測

	// セットカウント

};
