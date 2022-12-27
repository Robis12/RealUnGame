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


	// ��� Idle ���·� �ִٴ� ��.
	return EBTNodeResult::InProgress;
}


void URealUn_IdleTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Target�� ������ idle�� ����Ǳ� ����
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

