// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"

AFightingGameMode::AFightingGameMode()	
{
	PrimaryActorTick.bCanEverTick = true;

	////プレイヤーキャラを指定
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Main/0231honma/BP/BP_Player1"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

void AFightingGameMode::BeginPlay()
{
    Super::BeginPlay();
}

// 接続されているコントローラを出力する
void AFightingGameMode::GetAllConnectionDevice(TArray<FInputDeviceId>& OutInputDevices)
{
    //IPlatformInputDeviceMapper::Get().GetAllConnectedInputDevices(OutInputDevices);
}