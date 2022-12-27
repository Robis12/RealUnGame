// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUn_ItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"




void URealUn_ItemSlot::NativeConstruct()
{
	int a = 0;
}

void URealUn_ItemSlot::SlotInit()
{
	Image = Cast<UImage>(GetWidgetFromName(TEXT("ItemIconImage")));
	
	if (nullptr == Image)
	{
		UE_LOG(LogTemp, Error, TEXT("Item Image nullptr!"));
		return;
	}


	ItemCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));

	if (nullptr == ItemCountText)
	{
		UE_LOG(LogTemp, Error, TEXT("ItemCountText nullptr!"));
		return;
	}
	
	ItemCountString = TEXT("");

	Data = nullptr;
	// ItemCountString = TEXT("5");
	// Image->SetItem
}


void URealUn_ItemSlot::SetItemData(const FItemData* _Data)
{
	if (_Data->UseType != ContentsItemType::Use)
	{
		ItemCountString = TEXT("");
	}
	else if (_Data->UseType != ContentsItemType::Equip)
	{
		// 내가 사용 아이템이다.
		
		if (ItemCountString == TEXT(""))
		{
			// 한번도 아이템 갯수를 센 적이 없다는 것.
			ItemCountString = FString::FromInt(1);
		}
		else
		{
			int Count = FCString::Atoi(*ItemCountString);
			++Count;
			ItemCountString = FString::FromInt(Count);
		}
		
	}

	Image->SetBrushFromTexture(_Data->Icon);

	Data = _Data;
}

// 아이템이 이 슬롯에서 빠져나갔다. --> 그 슬롯에 아이템이 존재하지 않음
void URealUn_ItemSlot::ClearItemData()
{
	Data = nullptr;
}