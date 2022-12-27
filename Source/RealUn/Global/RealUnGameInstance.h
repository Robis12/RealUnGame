// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
// #include "../Play/UI/RealUn_Inventory.h"
#include "RealUnGameInstance.generated.h"



UCLASS()
class REALUN_API URealUnGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URealUnGameInstance();

	const struct FRealUnMonsterInfo* GetMonsterData(FName _Name) const;
	TSubclassOf<AActor> GetObjectData(FName _Name) const;
	const struct FItemData* GetItemData(FName _Name) const;

	TArray<const struct FItemData*> GetRandomDropData(int _Count);
	
	FORCEINLINE FRandomStream& GetRandomStream() { return Stream; }

	FORCEINLINE class URealUn_Inventory* GetInven() { return Inven; }

	FORCEINLINE void SetInven(class URealUn_Inventory* _Inven) { Inven = _Inven; }

	void DebugSwitch();
	FORCEINLINE bool IsDebug() { return DebugCheck; }

private:
	UPROPERTY()
	TSoftObjectPtr<class UDataTable> MonsterDataTable;
	UPROPERTY()
	TSoftObjectPtr<class UDataTable> ObjectDataTable;
	UPROPERTY()
	TSoftObjectPtr<class UDataTable> ItemDataTable;

	UPROPERTY()
	TArray<int32> ItemRandomTableIndex;

	TArray<const struct FItemData*> ItemDataRandomTable;

	UPROPERTY()
	FRandomStream Stream; // 난수 생성기

	UPROPERTY()
	class URealUn_Inventory* Inven;
	
	bool DebugCheck;
};
