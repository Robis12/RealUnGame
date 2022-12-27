// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RealUn/Play/RealUnCharacter.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "RealUn_Attack_AnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUn_Attack_AnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	// 최소한 여기까지는 애니메이션을 재생해야 한다.
	UPROPERTY(Category = "AnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MinAnimationPercent;	// 퍼센트 --> 최소한 20%는 재생되고 나서 다른 애니메이션으로 바꿀 수 있다.

	UPROPERTY(Category = "AnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	DefaultAnimation EndChangeAnimation;


protected:
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
