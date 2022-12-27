// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RealUn/Global/RealUnStructs.h"
#include "RealUn_ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUn_ItemSlot : public UUserWidget
{
	GENERATED_BODY()


public:


	FORCEINLINE const FItemData* GetItemData() { return Data; }
	void SetItemData(const FItemData* _Data);

	void ClearItemData();

protected:
	// �𸮾�ּ��� UI�� �ٸ��ٰ� �� --> BeginPlay ���� �༮��
	void NativeConstruct() override;




private:
	const FItemData* Data;

	class UImage* Image;

	class UTextBlock* ItemCountText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FString ItemCountString;


	UFUNCTION(BlueprintCallable, Category = "Contexnts", meta = (AllowPrivateAccess = "true"))
	void SlotInit();
};
