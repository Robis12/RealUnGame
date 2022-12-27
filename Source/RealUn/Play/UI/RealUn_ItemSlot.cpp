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
		// ���� ��� �������̴�.
		
		if (ItemCountString == TEXT(""))
		{
			// �ѹ��� ������ ������ �� ���� ���ٴ� ��.
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

// �������� �� ���Կ��� ����������. --> �� ���Կ� �������� �������� ����
void URealUn_ItemSlot::ClearItemData()
{
	Data = nullptr;
}