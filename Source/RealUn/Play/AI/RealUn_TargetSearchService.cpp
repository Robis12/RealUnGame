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

	AMonster* Monster = Con->GetPawn<AMonster>();		// 컨트롤러는 특정 폰을 컨트롤 하는거기 때문에 Owner를 가지는 것은 안됨.

	float SeeRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName("SeeRange"));



	if (URealUnBlueprintFunctionLibrary::IsDebug())
	{
		DrawDebugSphere(GetWorld(), Con->GetPawn()->GetActorLocation(), SeeRange, 50, FColor::Red, false, Interval);
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		Target = Monster->TargetSearch(FName(TEXT("Player")), SeeRange);

		// 타겟이 있으면 설정 없으면 없는대로 nullptr 설정
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
