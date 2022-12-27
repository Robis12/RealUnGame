// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RealUn/Global/RealUnStructs.h"
#include "RealUn_InvenSlotData.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUn_InvenSlotData : public UObject
{
	GENERATED_BODY()
	

public:
	const FItemData* ItemData;

};
