// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUn_TargetMoveTask.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RealUn/Play/RealUnAIController.h"
#include "RealUn/Play/Monster.h"
#include "RealUn/Global/RealUnStructs.h"
#include "RealUn/Global/RealUnBlueprintFunctionLibrary.h"
#include "NavigationSystem.h"
#include "RealUn/Global/RealUnGameInstance.h"



URealUn_TargetMoveTask::URealUn_TargetMoveTask()
{
	bNotifyTick = true;
}

EBTNodeResult::Type URealUn_TargetMoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ARealUnAIController* Con = Cast<ARealUnAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Con->GetPawn<AMonster>();
	const FRealUnMonsterInfo* MonsterInfo = Monster->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		// �ٽ� Idle ���·� ���ư��� ��.
		return EBTNodeResult::Succeeded;
	}


	AActor* TargetActor = Cast<AActor>(Target);

	if (Monster->GetTargetDir(TargetActor).Size() < MonsterInfo->AttRange)
	{
		Monster->ResetPath();
		// �������� ������ �Ѵٴ� ��.
		return EBTNodeResult::Failed;
	}

	UNavigationPath* FindPath = Monster->GetPath();

	if (nullptr != FindPath)
	{
		// ��� �̵��Ѵ�.
		if (false == Monster->PathMove())
		{
			Monster->ResetPath();
			return EBTNodeResult::InProgress;
		}

		if (100.0f >= Monster->GetLastPathPointToTargetDis(TargetActor->GetActorLocation()))
		{
			Monster->ResetPath();
			return EBTNodeResult::InProgress;
		}
	}


	// �̵��� �ΰ����� �Ǿ����
	FindPath = Monster->PathFind(TargetActor);

	if (nullptr != FindPath && false == FindPath->PathPoints.IsEmpty())
	{
		Monster->SetPath(FindPath, false);
		Monster->PathMove();
		return EBTNodeResult::InProgress;
	}
	

	Monster->SetTargetLook(TargetActor);
	Monster->SetTargetMovementInput(TargetActor);
	Monster->GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Forward);



	// ��� Idle ���·� �ִٴ� ��.
	return EBTNodeResult::InProgress;
}

void URealUn_TargetMoveTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
