// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnGameInstance.h"
#include "Global/RealUnStructs.h"

// 

URealUnGameInstance::URealUnGameInstance()
	: DebugCheck(false)
{
	Stream = FRandomStream(FDateTime::Now().GetTicks());

	{
		FString DataPath = TEXT("DataTable'/Game/Resources/Global/Data/MonsterData1.MonsterData1'");

		// 리소스를 생성자 수준에서 로드하기 위해 사용
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			MonsterDataTable = DataTable.Object;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("MonsterDatas Null!"));
		}
	}


	{
		FString DataPath = TEXT("DataTable'/Game/Resources/Global/Data/ObjectTable.ObjectTable'");

		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			ObjectDataTable = DataTable.Object;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ObjectDatas Null!"));
		}
	}



	{
		FString DataPath = TEXT("DataTable'/Game/Resources/Global/Data/ItemDataTable.ItemDataTable'");

		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			ItemDataTable = DataTable.Object;

			ItemDataTable->GetAllRows(nullptr, ItemDataRandomTable);

			for (size_t i = 1; i < ItemDataRandomTable.Num(); i++)
			{
				ItemRandomTableIndex.Add(i);
			}

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ItemDatas Null!"));
		}
	}

}



const FRealUnMonsterInfo* URealUnGameInstance::GetMonsterData(FName _Name) const
{
	if (nullptr == MonsterDataTable)
	{
		return nullptr;
	}

	FRealUnMonsterInfo* findTable = MonsterDataTable->FindRow<FRealUnMonsterInfo>(_Name, _Name.ToString());

	if (nullptr == findTable)
	{
		return nullptr;
	}

	return findTable;
}

TSubclassOf<AActor> URealUnGameInstance::GetObjectData(FName _Name) const
{
	if (nullptr == ObjectDataTable)
	{
		return nullptr;
	}

	FObjectTable* findTable = ObjectDataTable->FindRow<FObjectTable>(_Name, _Name.ToString());

	if (nullptr == findTable)
	{
		return nullptr;
	}

	return findTable->ObjectSubClass;

}

const FItemData* URealUnGameInstance::GetItemData(FName _Name) const
{
	if (nullptr == ItemDataTable)
	{
		return nullptr;
	}

	FItemData* findTable = ItemDataTable->FindRow<FItemData>(_Name, _Name.ToString());

	if (nullptr == findTable)
	{
		return nullptr;
	}

	return findTable;
}

// 2가 들어왔다.
TArray<const FItemData*> URealUnGameInstance::GetRandomDropData(int _Count)
{
	// 100 개

	// 1 ~ 99

	for (size_t i = 0; i < 100; i++)
	{
		int Right = Stream.RandRange(0, ItemRandomTableIndex.Num() - 1);
		int Left = Stream.RandRange(0, ItemRandomTableIndex.Num() - 1);

		int32 Temp = ItemRandomTableIndex[Right];
		ItemRandomTableIndex[Right] = ItemRandomTableIndex[Left];
		ItemRandomTableIndex[Left] = Temp;
	}

	TArray<const FItemData*> ResultArr;

	for (size_t i = 0; i < _Count; i++)
	{
		int32 RandomItemIndex = ItemRandomTableIndex[i];
		ResultArr.Add(ItemDataRandomTable[RandomItemIndex]);
	}


	return ResultArr;
}


void URealUnGameInstance::DebugSwitch()
{
	DebugCheck = !DebugCheck;

	if (DebugCheck)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Debug Check On"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Debug Check Off"));
	}
}
