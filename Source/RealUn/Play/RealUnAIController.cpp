// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnAIController.h"
#include "RealUn/Play/RealUnAICharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardData.h"

void ARealUnAIController::OnPossess(APawn* _Mon)
{
	Super::OnPossess(_Mon);

	ARealUnAICharacter* AiCharacter = Cast<ARealUnAICharacter>(_Mon);

	if (nullptr == AiCharacter
		|| false == AiCharacter->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("AiCharacter Cast Error!"));

		return;
	}


	if (nullptr == AiCharacter->GetBlackboardData()
		|| false == AiCharacter->GetBlackboardData()->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("GetBlackboardData Error!"));

		return;
	}

	if (nullptr == AiCharacter->GetBehaviorTree()
		|| false == AiCharacter->GetBehaviorTree()->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("GetBehaviorTree Error!"));

		return;
	}



	UBlackboardComponent* pBlackboardComponent = GetBlackboardComponent();
	UseBlackboard(AiCharacter->GetBlackboardData(), pBlackboardComponent);	// 블랙보드를 사용하겠다.

	RunBehaviorTree(AiCharacter->GetBehaviorTree());	// 행동트리를 동작

}
