// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnStaticMeshActor.h"

#include "RealUn/Global/RealUnSceneComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ARealUnStaticMeshActor::ARealUnStaticMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SceneComponent = CreateDefaultSubobject<URealUnSceneComponent>("RealUnSceneComponent");

	RootComponent = SceneComponent;
	

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	//StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	StaticMeshComponent->Mobility = EComponentMobility::Movable;
	//StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->bUseDefaultCollision = false;
	StaticMeshComponent->SetupAttachment(RootComponent);


	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	//SphereComponent->bUseDefaultCollision = true;
	SphereComponent->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void ARealUnStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARealUnStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

