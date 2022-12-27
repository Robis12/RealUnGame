// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUn_Inventory.h"
#include "RealUn/Global/RealUnGameInstance.h"
#include "RealUn/Global/ContantValues.h"
#include "Components/TileView.h"
#include "RealUn_InvenSlotData.h"
#include "RealUn_ItemSlot.h"



void URealUn_Inventory::InvenInit(UTileView* _TileView, int32 _Count)
{
	if (nullptr == _TileView)
	{
		return;
	}

	URealUnGameInstance* RealUnGameInstance = GetWorld()->GetGameInstance<URealUnGameInstance>();
	if (nullptr == RealUnGameInstance
		&& false == RealUnGameInstance->IsValidLowLevel())
	{
		return;
	}


	const FItemData* Data = RealUnGameInstance->GetItemData(ItemNames::NoneItem);

	for (size_t i = 0; i < _Count; i++)
	{
		URealUn_InvenSlotData* Inven = NewObject<URealUn_InvenSlotData>();
		Inven->ItemData = Data;
		//Inven->Index = i;
		_TileView->AddItem(Inven);
	}

	InitCount = _Count;

	RealUnGameInstance->SetInven(this);

}


// UUserWidget --> 아이템 슬롯 하나하나
int URealUn_Inventory::AddInvenItemEvent(UObject* _StartData, UUserWidget* _Slot)
{
	URealUn_InvenSlotData* Data = Cast< URealUn_InvenSlotData>(_StartData);

	if (nullptr == Data)
	{
		return 1;
	}


	URealUn_ItemSlot* Widget = Cast<URealUn_ItemSlot>(_Slot);

	if (nullptr == Widget)
	{
		return 1;
	}

	ItemSlots.Add(Widget);

	return --InitCount;
}



bool URealUn_Inventory::IsFull(const FItemData* _ItemData)
{

	if (_ItemData->UseType == ContentsItemType::Equip)
	{
		// 장비면 겹칠 수 없으므로
		for (size_t i = 0; i < ItemSlots.Num(); i++)
		{
			if (nullptr == ItemSlots[i]->GetItemData())
			{
				return false;
			}
		}
	}
	else if (_ItemData->UseType == ContentsItemType::Use)
	{
		for (size_t i = 0; i < ItemSlots.Num(); i++)
		{
			// 나랑 같은 종류의 소비아이템이 들어가있음
			if (_ItemData == ItemSlots[i]->GetItemData())
			{
				// 꽉 차지 않았으니 false
				return false;
			}
			// 나랑 같은게 없었음
			// 인벤 안에 포션이 하나도 없었음
		}

		for (size_t i = 0; i < ItemSlots.Num(); i++)
		{
			if (nullptr == ItemSlots[i]->GetItemData())
			{
				return false;
			}
		}
	}

	return true;
}


// 내가 _Data 먹었어
void URealUn_Inventory::AddItem(const FItemData* _Data)
{
	// 10개의 아이템 슬롯 중 어디로 들어갈거냐??
	if (_Data->UseType == ContentsItemType::Equip)
	{
		for (size_t i = 0; i < ItemSlots.Num(); i++)
		{
			// 이미 차있는 아이템 슬롯이기 때문에 들어갈 수 없다.
			if (nullptr != ItemSlots[i]->GetItemData())
			{
				continue;
			}

			// 
			ItemSlots[i]->SetItemData(_Data);
			return;
		}
	}
	else if (_Data->UseType == ContentsItemType::Use)
	{
		for (size_t i = 0; i < ItemSlots.Num(); i++)
		{
			// 같은 종류의 포션이 있다면 그 자리에 들어가야한다.
			if (_Data == ItemSlots[i]->GetItemData())
			{
				ItemSlots[i]->SetItemData(_Data);
				return;
			}
		}

		for (size_t i = 0; i < ItemSlots.Num(); i++)
		{
			// 여기까지 왔다면 같은 종류의 포션은 없을 것이고
			// 빈 자리의 인벤토리를 찾아서 그 곳에 넣어야한다.
			if (nullptr != ItemSlots[i]->GetItemData())
			{
				continue;
			}

			ItemSlots[i]->SetItemData(_Data);
			return;
		}
	}

}
