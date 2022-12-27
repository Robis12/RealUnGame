// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RealUnSpawnComponent.generated.h"

//enum SpawnType
//{
//	Sphere,
//	Box,
//};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REALUN_API URealUnSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URealUnSpawnComponent();

	void Init(int Seed);

protected:
	// Called when the game starts
	void BeginPlay() override;
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "RealUn")
	void DebugDraw();
	


private:
	// 어떤 액터를 생성할거냐?
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AActor>> SpawnActorsClass;

	
	// 얼마만에 생성할거냐?
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnTime;

	// 한번에 얼마나 만들거냐.
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int SpawnCount;

	// 최대 몇마리까지 할거냐?
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int MaxCount;	// -1 이라면 제한 없음 계속 생성

	// 원형으로 볼 것.
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnRange;	// 0 이면 그냥 그 위치에 생성되는 것.

	TArray<TObjectPtr<AActor>> SpawnActors;
	
	// 
	FRandomStream Stream; // 난수 생성기

		
};
