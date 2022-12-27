// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "PlayCharacter.h"

#include "PlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class PlayerAnimation : uint8
{
	Idle UMETA(DisplayName = "서있는 모션"),
	Left UMETA(DisplayName = "왼쪽"),     
	Right  UMETA(DisplayName = "오른쪽"), 
	Forward = 4 UMETA(DisplayName = "앞"),
	LeftForward = 5 UMETA(DisplayName = "왼쪽앞"), 
	RightForward = 6 UMETA(DisplayName = "오른쪽앞"),
	BackWard = 8 UMETA(DisplayName = "뒤"),  
	LeftBackWard = 9 UMETA(DisplayName = "왼쪽뒤"),
	RightBackWard = 10 UMETA(DisplayName = "오른쪽뒤"),
};

/**
 *
 */
UCLASS()
class REALUN_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents")
	PlayerAnimation AnimationState;

	UFUNCTION()
		FORCEINLINE PlayerAnimation GetAnimationState()
	{
		return AnimationState;
	}

};
