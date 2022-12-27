// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUn_AttackTask.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RealUn/Play/RealUnAIController.h"
#include "RealUn/Play/Monster.h"
#include "RealUn/Global/RealUnStructs.h"
#include "RealUn/Global/RealUnBlueprintFunctionLibrary.h"

URealUn_AttackTask::URealUn_AttackTask()
{
	bNotifyTick = true;
}

EBTNodeResult::Type URealUn_AttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ARealUnAIController* Con = Cast<ARealUnAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Con->GetPawn<AMonster>();
	const FRealUnMonsterInfo* MonsterInfo = Monster->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));


	if (nullptr == Target)
	{
		// 타겟이 없으면 다시 처음부터 실행해야함
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);
	FVector Dir = TargetActor->GetActorLocation() - Monster->GetActorLocation();

	if (false == Monster->GetIsRangeInTarget(TargetActor, MonsterInfo->AttRange))
	{
		return EBTNodeResult::Failed;
	}


	UAnimMontage* Montage = Monster->GetAnimationInst()->GetAnimation(DefaultAnimation::Attack);

	if (nullptr == Montage)
	{
		Monster->GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Idle);
		return EBTNodeResult::Failed;
	}

	Monster->GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Attack);
	WaitTime = Montage->CalculateSequenceLength();


	return EBTNodeResult::InProgress;
}

void URealUn_AttackTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// WaitTime에는 이 몽타주의 길이가 들어가있고
	WaitTime -= DeltaSeconds;

	if (0.0f < WaitTime)
	{
		return;
	}

	// 그만큼 기다렸음.
	WaitTime = 0.0f;

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
