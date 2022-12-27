// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RealUn/Play/RealUnStaticMeshActor.h"
#include "RealUnItemActor.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API ARealUnItemActor : public ARealUnStaticMeshActor
{
	GENERATED_BODY()
	

public:
	void SetItem(const struct FItemData* _ItemData);
	FORCEINLINE const struct FItemData* GetItem() { return ItemData; }

protected:
	virtual void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	const struct FItemData* ItemData;
};
