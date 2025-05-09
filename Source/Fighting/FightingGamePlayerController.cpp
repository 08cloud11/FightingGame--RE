// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingGamePlayerController.h"

AFightingGamePlayerController::AFightingGamePlayerController()
{

}

void AFightingGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AFightingGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}

FString AFightingGamePlayerController::_InputLever(const float X, const float Y)
{
	// ï‚ê≥å„ÇÃêîíl
	float _CorrectedX = 1.0f;
	float _CorrectedY = 1.0f;

	UE_LOG(LogTemp, Log, TEXT("%f"), X);
	UE_LOG(LogTemp, Log, TEXT("%f"), Y);
	return "";
}

void AFightingGamePlayerController::_InputCommand()
{

}