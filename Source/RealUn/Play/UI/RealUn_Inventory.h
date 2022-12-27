// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RealUn_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUn_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	bool IsFull(const FItemData* _ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InvenInit(class UTileView* _TileView, int32 _Count);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int AddInvenItemEvent(UObject* _StartData, UUserWidget* _Slot);

	void AddItem(const struct FItemData* _Data);


private:
	TArray<class URealUn_ItemSlot*> ItemSlots;

	int InitCount;
};
