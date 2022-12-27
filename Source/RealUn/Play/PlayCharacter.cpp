// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayCharacter.h"
#include "PlayerAnimInstance.h"
#include "Animation/RealUnAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"


#include "Components/SphereComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Global/RealUnBlueprintFunctionLibrary.h"


// Sets default values
APlayCharacter::APlayCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Player");

	{
		UCapsuleComponent* Com = FindComponentByClass<UCapsuleComponent>();
		if (nullptr != Com)
		{
			Com->SetCollisionProfileName(FName(TEXT("Player")));
		}
	}
}

// Called when the game starts or when spawned
void APlayCharacter::BeginPlay()
{
	Super::BeginPlay();

	// TSubClassOf
	UActorComponent* Component = GetComponentByClass(USpringArmComponent::StaticClass());

	if (nullptr == Component)
	{
		UE_LOG(LogTemp, Error, TEXT("USpringArmComponent Null!"));
		return;
	}

	SpringArmComponent = Cast<USpringArmComponent>(Component);
	if (nullptr == SpringArmComponent
		|| false == SpringArmComponent->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("USpringArmComponent Cast Error!"));
		return;
	}


	// 추가 애니메이션은 여기서 추가함
	for (auto& Anim : PlayerAnimations)
	{
		GetAnimationInst()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}

}

// Called every frame
void APlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// 캐릭터의 입력을 체크하기 위한 단계는 게임이 제대로 시작되기 전에 다 맞추어져 있어야 한다.
// Called to bind functionality to input
void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("GameLeftMove"), this, &APlayCharacter::LeftMove);
	PlayerInputComponent->BindAxis(TEXT("GameRightMove"), this, &APlayCharacter::RightMove);
	PlayerInputComponent->BindAxis(TEXT("GameForwardMove"), this, &APlayCharacter::ForwardMove);
	PlayerInputComponent->BindAxis(TEXT("GameBackwardMove"), this, &APlayCharacter::BackwardMove);
	PlayerInputComponent->BindAxis(TEXT("MouseMoveX"), this, &APlayCharacter::MouseMoveX);
	PlayerInputComponent->BindAxis(TEXT("MouseMoveY"), this, &APlayCharacter::MouseMoveY);

	PlayerInputComponent->BindAction(TEXT("AttLeft"), EInputEvent::IE_Pressed, this, &APlayCharacter::AttLeft);
	PlayerInputComponent->BindAction(TEXT("AttRight"), EInputEvent::IE_Pressed, this, &APlayCharacter::AttRight);
	PlayerInputComponent->BindAction(TEXT("GameLeftMove"), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(TEXT("GameRightMove"), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(TEXT("GameForwardMove"), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(TEXT("GameBackwardMove"), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);



	//int a = 0;

}

void APlayCharacter::LeftMove(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}

	if (true == IsAttack())
	{
		return;
	}

	AddMovementInput(-GetActorRightVector(), Value);

	// 이동은 해도 애니메이션은 안바꿈
	if (GetAnimationInst()->IsAnimMontage(DefaultAnimation::Forward)
		|| GetAnimationInst()->IsAnimMontage(DefaultAnimation::BackWard))
	{
		return;
	}


	GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Left);
}


void APlayCharacter::RightMove(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}

	if (true == IsAttack())
	{
		return;
	}

	AddMovementInput(GetActorRightVector(), Value);

	// 이동은 해도 애니메이션은 안바꿈
	if (GetAnimationInst()->IsAnimMontage(DefaultAnimation::Forward)
		|| GetAnimationInst()->IsAnimMontage(DefaultAnimation::BackWard))
	{
		return;
	}

	GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Right);
}
void APlayCharacter::ForwardMove(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}

	if (true == IsAttack())
	{
		return;
	}

	GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Forward);
	AddMovementInput(GetActorForwardVector(), Value);
}
void APlayCharacter::BackwardMove(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}

	if (true == IsAttack())
	{
		return;
	}

	GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::BackWard);
	AddMovementInput(-GetActorForwardVector(), Value);
}

void APlayCharacter::MouseMoveX(float Value)
{
	AddControllerYawInput(Value);
}

void APlayCharacter::MouseMoveY(float Value)
{
	if (nullptr == SpringArmComponent)
	{
		return;
	}

	if (Value == 0.0f)
	{
		return;
	}



	FRotator NextRot = GetControlRotation();
	NextRot.Add(Value * 3.0f, 0., 0.);
	FVector3d EulerRot = NextRot.Euler();

	

	if (EulerRot.Y > 10 && EulerRot.Y < 300)
	{

		
		return;
	}

	SpringArmComponent->TargetArmLength -= Value * 3.f;

	AddControllerPitchInput(-Value);

	
}

void APlayCharacter::MoveKeyEnd()
{
	GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Idle);
}


void APlayCharacter::DamageOn()
{
	TArray<UActorComponent*> Array = GetDamageCollision();

	for (size_t i = 0; i < Array.Num(); ++i)
	{
		bool Check = false;
		USphereComponent* Sphere = Cast<USphereComponent>(Array[i]);

		if (nullptr == Sphere)
		{
			continue;
		}

		TArray<FHitResult> Targets = CollsionCheck(Sphere->GetComponentLocation()
			, FName(TEXT("PlayerAttackTrace"))
			, Sphere->GetCollisionShape());

		for (size_t MonsterCount = 0; MonsterCount < Targets.Num(); ++MonsterCount)
		{
			ARealUnCharacter* RealUn = Cast<ARealUnCharacter>(Targets[MonsterCount].GetActor());
			if (nullptr != RealUn)
			{
				Check = true;
				RealUn->CalDamage(1.0);
			}
		}

		FColor Color = FColor::Green;

		if (true == Check)
		{
			Color = FColor::Red;
		}
		DrawDebugSphere(GetWorld(), Sphere->GetComponentLocation(), Sphere->GetScaledSphereRadius(), 10, Color, false, 0.1f);
	}
}

bool APlayCharacter::IsAttack()
{
	if (true == GetAnimationInst()->IsAnimMontage(PlayerAnimationEx::AttackRight)
		|| true == GetAnimationInst()->IsAnimMontage(PlayerAnimationEx::AttackLeft))
	{
		return true;
	}

	return false;
}



void APlayCharacter::AttLeft()
{
	if (true == IsAttack())
	{
		return;
	}

	GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Attack);
}

void APlayCharacter::AttRight()
{
	if (true == IsAttack())
	{
		return;
	}
	double _MP = GetMP();
	if (_MP <= 0.0)
	{
		return;
	}
	_MP -= 1.0;
	SetMP(_MP);
	GetAnimationInst()->ChangeAnimMontage(PlayerAnimationEx::AttackRight);
}


void APlayCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation
	, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	int a = 0;
}


void APlayCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ARealUnCharacter* Character = Cast<ARealUnCharacter>(OtherActor);

	if (nullptr == Character)
	{
		// 캐릭터가 아닐 때의 처리
		return;
	}

	if (true == Character->ActorHasTag(FName(TEXT("Monster"))))
	{
		// 상대를 맞췄을 때
		CalDamage(1.0);
	}

	if (true == Character->ActorHasTag(FName(TEXT("Player"))))
	{
		// 내가 쳤을 때는 상대에게 데미지
		Character->CalDamage(1.0);
	}
}

void APlayCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	//UE_LOG(LogTemp, Error, TEXT("Monster Damage End!"));
}

