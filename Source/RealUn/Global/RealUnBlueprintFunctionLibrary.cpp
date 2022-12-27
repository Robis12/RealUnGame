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

	// ���� �����ϰ� �ִ� ��� ����� --> ������ â�� �ִ� World, �������Ʈ, Scene ��
	for (FWorldContext Context : GEngine->GetWorldContexts())
	{
		switch (Context.WorldType)
		{
			// Play ���� World
		case EWorldType::PIE:
			PIE = Context.World();
			break;
			// �������Ʈ, �����Ϳ��� ��� World �� �ִٸ�
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
