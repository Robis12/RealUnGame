// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUn_Attack_AnimNotifyState.h"


void URealUn_Attack_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	// MeshComp --> 나를 가진 스켈레톤 메시가 들어오니까 여기서 Owner Actor를 찾아온다.
	ARealUnCharacter* Actor = MeshComp->GetOwner<ARealUnCharacter>();
	if (nullptr == Actor
		&& false == Actor->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("URealUn_Attack_AnimNotifyState Actor Is Null"));
		return;
	}
	

	UE_LOG(LogTemp, Error, TEXT("Attack Start!"));
}

void URealUn_Attack_AnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	//UE_LOG(LogTemp, Error, TEXT("실행중!"));
}

void URealUn_Attack_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	//UE_LOG(LogTemp, Error, TEXT("끝!"));

	ARealUnCharacter* Actor = MeshComp->GetOwner<ARealUnCharacter>();
	if (nullptr == Actor
		&& false == Actor->IsValidLowLevel())
	{
		//UE_LOG(LogTemp, Error, TEXT("URealUn_Attack_AnimNotifyState Actor Is Null"));
		return;
	}

	if (EndChangeAnimation == DefaultAnimation::Default)
	{
		return;
	}
	
	Actor->GetAnimationInst()->ChangeAnimMontage(EndChangeAnimation/*, 0.0f, true*/);
}
