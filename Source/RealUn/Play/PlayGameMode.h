// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API APlayGameMode : public AGameMode
{
	GENERATED_BODY()
	

	void BeginPlay() override;
};
