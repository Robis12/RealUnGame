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


// UUserWidget --> ������ ���� �ϳ��ϳ�
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
		// ���� ��ĥ �� �����Ƿ�
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
			// ���� ���� ������ �Һ�������� ������
			if (_ItemData == ItemSlots[i]->GetItemData())
			{
				// �� ���� �ʾ����� false
				return false;
			}
			// ���� ������ ������
			// �κ� �ȿ� ������ �ϳ��� ������
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


// ���� _Data �Ծ���
void URealUn_Inventory::AddItem(const FItemData* _Data)
{
	// 10���� ������ ���� �� ���� ���ų�??
	if (_Data->UseType == ContentsItemType::Equip)
	{
		for (size_t i = 0; i < ItemSlots.Num(); i++)
		{
			// �̹� ���ִ� ������ �����̱� ������ �� �� ����.
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
			// ���� ������ ������ �ִٸ� �� �ڸ��� �����Ѵ�.
			if (_Data == ItemSlots[i]->GetItemData())
			{
				ItemSlots[i]->SetItemData(_Data);
				return;
			}
		}

		for (size_t i = 0; i < ItemSlots.Num(); i++)
		{
			// ������� �Դٸ� ���� ������ ������ ���� ���̰�
			// �� �ڸ��� �κ��丮�� ã�Ƽ� �� ���� �־���Ѵ�.
			if (nullptr != ItemSlots[i]->GetItemData())
			{
				continue;
			}

			ItemSlots[i]->SetItemData(_Data);
			return;
		}
	}

}
