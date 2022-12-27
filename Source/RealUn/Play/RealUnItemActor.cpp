// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnItemActor.h"
#include "RealUn/Global/RealUnStructs.h"
#include "RealUn/Global/RealUnGameInstance.h"
#include "RealUn/Play/UI/RealUn_Inventory.h"
#include "Components/SphereComponent.h"


void ARealUnItemActor::SetItem(const FItemData* _ItemData)
{
	if (nullptr == _ItemData)
	{
		return;
	}

	if (nullptr == _ItemData->DropMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Drop Item Mesh Is nullptr!"), *_ItemData->DisplayName.ToString());
		return;
	}
	

	GetStaticMeshComponent()->SetStaticMesh(_ItemData->DropMesh);
	ItemData = _ItemData;
}

void ARealUnItemActor::BeginPlay()
{
	Super::BeginPlay();

	GetSphereComponent()->SetCollisionProfileName(TEXT("Item"));
}

void ARealUnItemActor::Tick(float _DeltaTime)
{
	FRotator Rot = GetStaticMeshComponent()->GetRelativeRotation();
	Rot.Yaw += 1.f;
	GetStaticMeshComponent()->SetRelativeRotation(Rot);
}

void ARealUnItemActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	URealUnGameInstance* RealUnGameInstance = GetWorld()->GetGameInstance<URealUnGameInstance>();
	if (nullptr == RealUnGameInstance
		&& false == RealUnGameInstance->IsValidLowLevel())
	{
		return;
	}


	// 아이템이 충돌했는데 인벤이 꽉 차있을 때 --> 아이템이 사라지면 안됨!!
	if (true == RealUnGameInstance->GetInven()->IsFull(ItemData))
	{
		return;
	}

	RealUnGameInstance->GetInven()->AddItem(ItemData);

	Destroy();
}
