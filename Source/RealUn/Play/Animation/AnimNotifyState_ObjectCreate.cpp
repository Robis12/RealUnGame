// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_ObjectCreate.h"
#include "RealUn/Play/RealUnProjectile.h"
#include "RealUn/Global/RealUnBlueprintFunctionLibrary.h"

void UAnimNotifyState_ObjectCreate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (nullptr == URealUnBlueprintFunctionLibrary::GetCurrentPlayWorld())
	{
		return;
	}

	if (nullptr == SpawnActorsClass
		|| false == SpawnActorsClass->IsValidLowLevel())
	{
		return;
	}

	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	// ���� ������ �ִϸ��̼� �� ��� ������ ������ �� ����
	FVector Pos = MeshComp->GetSocketLocation(SocketName);


	FTransform SpawnTransform = FTransform(Pos);
	
	SpawnTransform.SetRotation(MeshComp->GetOwner()->GetTransform().GetRotation());

	AActor* NewActor = MeshComp->GetWorld()->SpawnActorDeferred<AActor>(SpawnActorsClass, SpawnTransform);
	ARealUnProjectile* Projectile = Cast<ARealUnProjectile>(NewActor);
	Projectile->SetInfo(CollisionName, Speed, LifeTime);
	NewActor->FinishSpawning(SpawnTransform);



}
