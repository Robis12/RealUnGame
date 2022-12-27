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
	// � ���͸� �����Ұų�?
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AActor>> SpawnActorsClass;

	
	// �󸶸��� �����Ұų�?
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnTime;

	// �ѹ��� �󸶳� ����ų�.
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int SpawnCount;

	// �ִ� ������� �Ұų�?
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int MaxCount;	// -1 �̶�� ���� ���� ��� ����

	// �������� �� ��.
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnRange;	// 0 �̸� �׳� �� ��ġ�� �����Ǵ� ��.

	TArray<TObjectPtr<AActor>> SpawnActors;
	
	// 
	FRandomStream Stream; // ���� ������

		
};
