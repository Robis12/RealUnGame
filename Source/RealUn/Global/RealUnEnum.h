// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RealUnEnum.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUnEnum : public UObject
{
	GENERATED_BODY()
	
};


// 모든 오브젝트들이 사용할 수 있는 기본적인 애니메이션
UENUM(BlueprintType)
enum class DefaultAnimation : uint8
{
	Default UMETA(DisplayName = "애니메이션 지정안됨"),
	Idle UMETA(DisplayName = "서있는 모션"),
	Left UMETA(DisplayName = "왼쪽"),      
	Right  UMETA(DisplayName = "오른쪽"),  
	Forward UMETA(DisplayName = "앞"), 
	BackWard UMETA(DisplayName = "뒤"), 
	Attack UMETA(DisplayName = "공격모션"),
	Max UMETA(DisplayName = "최대치"),
};

UENUM(BlueprintType)
enum class ContentsItemType : uint8
{
	// 없는 아이템
	Default UMETA(DisplayName = "아이템 타입 없음"),
	// 절대로 겹칠 수 없음
	Equip UMETA(DisplayName = "장비"),
	// 무조건 겹침
	Use UMETA(DisplayName = "소비"),
};