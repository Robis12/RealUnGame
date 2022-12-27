// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RealUnAIController.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API ARealUnAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	void OnPossess(APawn* _Mon);

private:
	UBehaviorTree* BehaviorTree;
	UBlackboardData* BlackboardData;
};
