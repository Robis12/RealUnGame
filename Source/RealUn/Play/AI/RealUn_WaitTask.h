// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RealUn_WaitTask.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUn_WaitTask : public UBTTaskNode
{
	GENERATED_BODY()
	

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
