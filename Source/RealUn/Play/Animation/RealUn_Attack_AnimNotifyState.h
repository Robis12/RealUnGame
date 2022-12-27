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
	// �ּ��� ��������� �ִϸ��̼��� ����ؾ� �Ѵ�.
	UPROPERTY(Category = "AnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MinAnimationPercent;	// �ۼ�Ʈ --> �ּ��� 20%�� ����ǰ� ���� �ٸ� �ִϸ��̼����� �ٲ� �� �ִ�.

	UPROPERTY(Category = "AnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	DefaultAnimation EndChangeAnimation;


protected:
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
