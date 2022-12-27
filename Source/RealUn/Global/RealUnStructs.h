// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Animation/AnimMontage.h"
#include "../Play/RealUnCharacter.h"
#include "RealUnStructs.generated.h"


/**
 * 
 */
UCLASS()
class REALUN_API URealUnStructs : public UObject
{
	GENERATED_BODY()
	
};


// 앞으로 만들어질 왠만한 구조체들은 전부 다 여기서 처리함.

// Atomic --> 데이터를 직렬화 해서 메모리를 아끼라는 것
// 데이터를 수천 수만개 써야할 때 속력을 빠르게 해줌
USTRUCT(Atomic, BlueprintType)
struct FRealUnMonsterInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Def;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double MinAtt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double MaxAtt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double SeeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double AttRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<DefaultAnimation, class UAnimMontage*> Animations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInterface* MinimapIcon;
};



USTRUCT(Atomic, BlueprintType)
struct FRealUnSkillInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double Hp;

	// Vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> TestVector;

	// Map
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, int> TestMap;
};




USTRUCT(Atomic, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ContentsItemType UseType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* DropMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Mp;
};


USTRUCT(Atomic, BlueprintType)
struct FObjectTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> ObjectSubClass;
};