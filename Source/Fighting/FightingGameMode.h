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
	int _ControllerID;		// �R���g���[���[
	int _PlayerNum;			// ����\�ȃv���C���[��

	/*UPROPERTY()
	TArray<AMyCharacter*> PlayerActor;*/

	/*UPROPERTY()
	TArray<AMyPlayerController*> PlayerContoloer;*/

private:
	// �R���g���[���[�ƃv���C���[�̐ڑ�������֐�

	// �v���C���[�𐶐�����
	void _CreateToPlayer();

	// �v���C���[��HP���擾����
	template<typename PlayerType >void _SetPlayerHP(PlayerType* Player);

	// ���s����

	// ���Ԍv��

	// �Z�b�g�J�E���g

};
