// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"
#include "Player2_Demo.h"

AFightingGameMode::AFightingGameMode()	
{
	PrimaryActorTick.bCanEverTick = true;

	//"Blueprint'/Game/Blueprints/CodeBlueprints/Characters/BP_Nagy.BP_Nagy_C'"

	//プレイヤーキャラを指定
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Main/0231honma/BP/BP_Player.BP_Player_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AFightingGameMode::StartPlay()
{
	Super::StartPlay();

	//2Pキャラ生成処理。エラー修正中
	/*FTransform spawntr;
	FVector pos = FVector(0.0, 300.0, 90.0);
	spawntr.SetLocation(pos);

	FString path = TEXT("/Game/Main/0231honma/BP/BP_Sandbag");
	TSubclassOf<class AActor> Player2 = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();

	ACharacter* spawnplayer = Cast<ACharacter>(GetWorld()->SpawnActor<AActor>(Player2, spawntr));

	APlayerController* controller = UGameplayStatics::CreatePlayer(GetWorld());
	controller->Possess(spawnplayer);

	Cast<APlayer2_Demo>(spawnplayer)->SetInput(controller);*/
}