// Fill out your copyright notice in the Description page of Project Settings.


#include "RUStaticMeshActor.h"
#include "Components/MeshComponent.h"


ARUStaticMeshActor::ARUStaticMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARUStaticMeshActor::BeginPlay()
{
	TArray<UActorComponent*> Arr = GetComponentsByClass(UMeshComponent::StaticClass());
	
	for (size_t i = 0; i < Arr.Num(); i++)
	{
		UMeshComponent* Ptr = Cast<UMeshComponent>(Arr[i]);
		if (nullptr == Ptr)
		{
			continue;
		}

		Ptr->bHiddenInSceneCapture = true;
	}
}
