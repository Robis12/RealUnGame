// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "RealUn/Play/RealUnCharacter.h"

// Sets default values
ARealUnProjectile::ARealUnProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DamageCollision"));

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARealUnProjectile::OnCollisionEnter);

	RootComponent = SphereComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	// 투사체 중력
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	Damage = 5.0f;
}



// Called when the game starts or when spawned
void ARealUnProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * Speed;
}

// Called every frame
void ARealUnProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (0.0f >= (LifeTime -= DeltaTime))
	{
		Destroy();
	}
}

void ARealUnProjectile::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComponent
	, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	ARealUnCharacter* Character = Cast<ARealUnCharacter>(_pOtherActor);

	if (nullptr == Character)
	{
		return;
	}

	Character->CalDamage(Damage);

	Destroy();
}


void ARealUnProjectile::SetInfo(FName _CollisionProfileName,float _Speed, float _LifeTime)
{
	Speed = _Speed;
	LifeTime = _LifeTime;

	SphereComponent->SetCollisionProfileName(_CollisionProfileName);
}