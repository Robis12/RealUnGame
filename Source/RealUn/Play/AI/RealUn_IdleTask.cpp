// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUn_IdleTask.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RealUn/Play/RealUnAIController.h"
#include "RealUn/Play/Monster.h"
#include "RealUn/Global/RealUnStructs.h"
#include "RealUn/Global/RealUnBlueprintFunctionLibrary.h"



URealUn_IdleTask::URealUn_IdleTask()
{
	bNotifyTick = true;
}


EBTNodeResult::Type URealUn_IdleTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ARealUnAIController* Con = Cast<ARealUnAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Con->GetPawn<AMonster>();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));


	if (nullptr != Target)
	{
		return EBTNodeResult::Failed;
	}

	Monster->GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Idle);


	// 계속 Idle 상태로 있다는 것.
	return EBTNodeResult::InProgress;
}


void URealUn_IdleTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Target이 잡히면 idle이 종료되길 원함
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

