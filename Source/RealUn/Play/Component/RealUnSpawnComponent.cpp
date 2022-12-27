// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnSpawnComponent.h"
#include "Global/RealUnBlueprintFunctionLibrary.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
URealUnSpawnComponent::URealUnSpawnComponent()
// ���� �ð����� ������
	: Stream(FDateTime::Now().GetTicks())	// �𸮾󿡼��� �ð�
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

	// ...
}

void URealUnSpawnComponent::Init(int Seed)
{
	Stream = FRandomStream();
}


// Called when the game starts
void URealUnSpawnComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.TickInterval = SpawnTime;




	// Stream = FRandomStream(ServerSeed);
	
}


// Called every frame
void URealUnSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Error, TEXT("Tick!!!!!"));


#if WITH_EDITOR
	DebugDraw();
#endif

	if (0 == MaxCount)
	{
		return;
	}

	if (true == SpawnActorsClass.IsEmpty())
	{
		return;
	}

	if (SpawnActors.Num() >= MaxCount)
	{
		return;
	}

	for (size_t i = 0; i < SpawnCount; ++i)
	{
		FVector NewVector = FVector(Stream.FRandRange(-SpawnRange, SpawnRange), Stream.FRandRange(-SpawnRange, SpawnRange), 0.0f);

		NewVector.Normalize();

		NewVector *= Stream.FRandRange(0., SpawnRange);

		NewVector += GetOwner()->GetActorLocation();

		int RandomSelect = Stream.RandRange(0, SpawnActorsClass.Num() - 1);


		FTransform SpawnTransform = FTransform(NewVector);
		// Begin Play�� �������� �ʰ� �ϴ� --> �� ��������� Begin Play�ϰ� ��.
		AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnActorsClass[RandomSelect], SpawnTransform);

		UCapsuleComponent* CapsuleComponent = NewActor->FindComponentByClass<UCapsuleComponent>();
		NewVector.Z += CapsuleComponent->GetScaledCapsuleHalfHeight();
		NewActor->FinishSpawning(FTransform(NewVector));
		// SpawnActorsClass[RandomSelect];

		SpawnActors.Add(NewActor);
		if (SpawnActors.Num() >= MaxCount)
		{
			return;
		}
	}
}

void URealUnSpawnComponent::DebugDraw()
{
	if (URealUnBlueprintFunctionLibrary::IsDebug())
	{
		DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), SpawnRange, 50, FColor::Red, false, SpawnTime);
	}
}
