// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUn_TargetSearchService.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RealUn/Play/RealUnAIController.h"
#include "RealUn/Play/Monster.h"
#include "RealUn/Global/RealUnStructs.h"
#include "RealUn/Global/RealUnBlueprintFunctionLibrary.h"

URealUn_TargetSearchService::URealUn_TargetSearchService()
{
	NodeName = TEXT("TargetSearch");

	Interval = 0.5f;
}

void URealUn_TargetSearchService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ARealUnAIController* Con = Cast<ARealUnAIController>(OwnerComp.GetAIOwner());

	AMonster* Monster = Con->GetPawn<AMonster>();		// ��Ʈ�ѷ��� Ư�� ���� ��Ʈ�� �ϴ°ű� ������ Owner�� ������ ���� �ȵ�.

	float SeeRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName("SeeRange"));



	if (URealUnBlueprintFunctionLibrary::IsDebug())
	{
		DrawDebugSphere(GetWorld(), Con->GetPawn()->GetActorLocation(), SeeRange, 50, FColor::Red, false, Interval);
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		Target = Monster->TargetSearch(FName(TEXT("Player")), SeeRange);

		// Ÿ���� ������ ���� ������ ���´�� nullptr ����
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), Target);
	}
	else
	{
		AActor* TargetActor = Cast<AActor>(Target);

		if (SeeRange < (TargetActor->GetActorLocation() - Monster->GetActorLocation()).Size())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), nullptr);
		}

	}







}
