// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "PlayCharacter.h"

#include "PlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class PlayerAnimation : uint8
{
	Idle UMETA(DisplayName = "���ִ� ���"),
	Left UMETA(DisplayName = "����"),     
	Right  UMETA(DisplayName = "������"), 
	Forward = 4 UMETA(DisplayName = "��"),
	LeftForward = 5 UMETA(DisplayName = "���ʾ�"), 
	RightForward = 6 UMETA(DisplayName = "�����ʾ�"),
	BackWard = 8 UMETA(DisplayName = "��"),  
	LeftBackWard = 9 UMETA(DisplayName = "���ʵ�"),
	RightBackWard = 10 UMETA(DisplayName = "�����ʵ�"),
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
