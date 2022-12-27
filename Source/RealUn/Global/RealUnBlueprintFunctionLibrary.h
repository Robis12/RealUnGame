// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RealUnGameInstance.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RealUnBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUnBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "RealUn|Global")
	static void OpenLevel(FName _OpenLevelName);

	// �����Ͱ� �÷������̰� �Ű� �Ⱦ��� ������ World�� ������
	static UWorld* GetCurrentPlayWorld();

	static URealUnGameInstance* GetRealUnInstance();

	UFUNCTION(BlueprintCallable, Category = "RealUn|Global")
	static void DebugSwitch();
	static bool IsDebug();
};
