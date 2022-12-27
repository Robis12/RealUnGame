// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUn_Damage_AnimNotifyState.h"
#include "RealUn/Play/RealUnCharacter.h"

void URealUn_Damage_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	UE_LOG(LogTemp, Error, TEXT("Damage Begin!"));

	// ¿©±â¼­ ÄÒ´Ù.
	ARealUnCharacter* Actor = MeshComp->GetOwner<ARealUnCharacter>();
	if (nullptr == Actor
		&& false == Actor->IsValidLowLevel())
	{
		//UE_LOG(LogTemp, Error, TEXT("URealUn_Attack_AnimNotifyState Actor Is Null"));
		return;
	}

	Actor->DamageOn();

	OnceFrame = false;
}

void URealUn_Damage_AnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	UE_LOG(LogTemp, Error, TEXT("Damage Tick!"));
	// ¿©±â¼­ ²ö´Ù.
	ARealUnCharacter* Actor = MeshComp->GetOwner<ARealUnCharacter>();
	if (nullptr == Actor
		&& false == Actor->IsValidLowLevel())
	{
		//UE_LOG(LogTemp, Error, TEXT("URealUn_Attack_AnimNotifyState Actor Is Null"));
		return;
	}

	if (OnceFrame == false)
	{
		OnceFrame = true;
		return;
	}

	Actor->DamageOff();
}

void URealUn_Damage_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	UE_LOG(LogTemp, Error, TEXT("Damage End!"));
	// ¿©±â¼­ ²ö´Ù.
}
