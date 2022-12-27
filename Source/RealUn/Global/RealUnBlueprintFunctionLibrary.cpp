// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void URealUnBlueprintFunctionLibrary::OpenLevel(FName _OpenLevelName)
{
	UWorld* CurrentWorld = GetCurrentPlayWorld();

	if (nullptr == CurrentWorld)
	{
		return;
	}

	UGameplayStatics::OpenLevel(CurrentWorld, _OpenLevelName);
}

UWorld* URealUnBlueprintFunctionLibrary::GetCurrentPlayWorld()
{
	UWorld* PIE = nullptr;
	UWorld* GamePreview = nullptr;

	// 현재 실행하고 있는 모든 월드들 --> 에디터 창에 있는 World, 블루프린트, Scene 등
	for (FWorldContext Context : GEngine->GetWorldContexts())
	{
		switch (Context.WorldType)
		{
			// Play 중인 World
		case EWorldType::PIE:
			PIE = Context.World();
			break;
			// 블루프린트, 에디터에서 띄운 World 가 있다면
		case EWorldType::GamePreview:
			GamePreview = Context.World();
			break;
		default:
			break;
		}
	}

	UWorld* CurrentWorld = nullptr;

	if (nullptr != PIE)
	{
		CurrentWorld = PIE;
	}
	else if (nullptr != GamePreview)
	{
		CurrentWorld = GamePreview;
	}

	return CurrentWorld;
}

URealUnGameInstance* URealUnBlueprintFunctionLibrary::GetRealUnInstance()
{
	URealUnGameInstance* RealUnInst = GetCurrentPlayWorld()->GetGameInstance<URealUnGameInstance>();

	if (nullptr == RealUnInst)
	{
		UE_LOG(LogTemp, Error, TEXT("URealUnGameInstance Null!"));

		return nullptr;
	}

	return RealUnInst;
}

void URealUnBlueprintFunctionLibrary::DebugSwitch()
{
	if (nullptr == GetCurrentPlayWorld())
	{
		return;
	}

	URealUnGameInstance* RealUnInst = GetCurrentPlayWorld()->GetGameInstance<URealUnGameInstance>();

	if (nullptr == RealUnInst)
	{
		UE_LOG(LogTemp, Error, TEXT("URealUnGameInstance Null!"));

		return;
	}

	RealUnInst->DebugSwitch();
}

bool URealUnBlueprintFunctionLibrary::IsDebug()
{
	URealUnGameInstance* RealUnInst = GetCurrentPlayWorld()->GetGameInstance<URealUnGameInstance>();

	if (nullptr == RealUnInst)
	{
		UE_LOG(LogTemp, Error, TEXT("URealUnGameInstance Null!"));

		return false;
	}

	return RealUnInst->IsDebug();
}
