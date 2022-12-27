// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RealUn_FadeObject.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUn_FadeObject : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable, Category = "Contents", meta = (AllowPrivateAccess = "true"))
		float ColorSetting(float _InDeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Contents", meta = (AllowPrivateAccess = "true"))
		void StartTimeSetting(float _WaitTime);


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FLinearColor StartColor;

	float WaitTime;
};
