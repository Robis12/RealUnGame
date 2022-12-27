// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RealUnAICharacter.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API AMonster : public ARealUnAICharacter
{
	GENERATED_BODY()
	

public:
	AMonster();

	FORCEINLINE const struct FRealUnMonsterInfo* GetMonsterData() { return MonsterData; }
	const struct FRealUnMonsterInfo* MonsterDataInit();

	FORCEINLINE bool Attack() 
	{
		bool Return = IsDamageCheck;
		DamageOff();
		return Return;
	}

	virtual void DamageOn() override;
	virtual void DamageOff() override;

	virtual void CalDamage(double _Damage) override;



protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	FName MonsterStatusKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> DamageCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> IconArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Plane;

	const struct FRealUnMonsterInfo* MonsterData;

	TArray<const struct FItemData*> DropTable;

	bool IsDamageCheck;




};
