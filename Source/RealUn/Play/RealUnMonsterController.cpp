// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnMonsterController.h"
#include "RealUn/Play/Monster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RealUn/Global/RealUnStructs.h"
//#include "Monster.h"


void ARealUnMonsterController::OnPossess(APawn* _Mon)
{
	Super::OnPossess(_Mon);

	AMonster* AiCharacter = Cast<AMonster>(_Mon);

	const struct FRealUnMonsterInfo* Data = AiCharacter->MonsterDataInit();

	if (nullptr == Data)
	{
		UE_LOG(LogTemp, Error, TEXT("MonsterData Empty! OnPossess"));
		return;
	}

	Blackboard->SetValueAsFloat("SeeRange", Data->SeeRange);
}
