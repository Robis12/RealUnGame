// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RealUn_AttackTask.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUn_AttackTask : public UBTTaskNode
{
	GENERATED_BODY()
private:
	float WaitTime;
		

public:
	URealUn_AttackTask();


protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
