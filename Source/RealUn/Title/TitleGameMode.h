// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TitleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API ATitleGameMode : public AGameMode
{
	GENERATED_BODY()

		//virtual void StartSetting()
		//{
		//	디폴트 폰클래스 = 
		//}

	void BeginPlay() override;
};
