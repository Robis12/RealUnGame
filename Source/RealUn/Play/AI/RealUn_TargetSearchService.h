// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RealUn_TargetSearchService.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUn_TargetSearchService : public UBTService
{
	GENERATED_BODY()
	

public:
	URealUn_TargetSearchService();


protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
