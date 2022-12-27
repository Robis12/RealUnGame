// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "RUStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API ARUStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ARUStaticMeshActor();

protected:
	virtual void BeginPlay() override;
};
