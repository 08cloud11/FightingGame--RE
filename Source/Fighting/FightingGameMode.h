#pragma once

#include "CharactorBase.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightingGameMode.generated.h"

UCLASS()
class FIGHTING_API AFightingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFightingGameMode();

	virtual void StartPlay() override;
};
