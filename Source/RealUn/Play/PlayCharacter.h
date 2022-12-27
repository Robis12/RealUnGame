// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Rotator.h"
#include "RealUnCharacter.h"
#include "GameFramework/Character.h"
#include "PlayCharacter.generated.h"




UENUM(BlueprintType)
enum class PlayerAnimationEx : uint8
{
	// 1100 
	Min UMETA(DisplayName = "사용하지 마시오"),
	Default UMETA(DisplayName = "애니메이션 지정안됨"),
	Idle UMETA(DisplayName = "서있는 모션"),
	Left UMETA(DisplayName = "왼쪽"),      // 0001
	Right  UMETA(DisplayName = "오른쪽"),  // 0010
	Forward UMETA(DisplayName = "앞"), // 0100
	BackWard UMETA(DisplayName = "뒤"),  // 1000
	AttackLeft UMETA(DisplayName = "공격모션"),  // 1000
	AttackRight UMETA(DisplayName = "플레이어 오른쪽 공격"),
	Skill1 UMETA(DisplayName = "스킬1"),
	Skill2 UMETA(DisplayName = "스킬2"),
	Skill3 UMETA(DisplayName = "스킬3"),
};


UCLASS()
class REALUN_API APlayCharacter : public ARealUnCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayCharacter();

	UFUNCTION(BlueprintCallable, Category = RealUn)
	void LeftMove(float Value);

	UFUNCTION(BlueprintCallable, Category = RealUn)
	void RightMove(float Value);

	UFUNCTION(BlueprintCallable, Category = RealUn)
	void ForwardMove(float Value);

	UFUNCTION(BlueprintCallable, Category = RealUn)
	void BackwardMove(float Value);

	UFUNCTION(BlueprintCallable, Category = RealUn)
	void MouseMoveX(float Value);

	UFUNCTION(BlueprintCallable, Category = RealUn)
	void MouseMoveY(float Value);

	UFUNCTION(BlueprintCallable, Category = RealUn)
	void MoveKeyEnd();

	UFUNCTION(BlueprintCallable, Category = RealUn)
	void AttLeft();

	UFUNCTION(BlueprintCallable, Category = RealUn)
	void AttRight();


	virtual void DamageOn() override;
	// virtual void DamageOff() override;

	bool IsAttack();



protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 기본적으로 오버랩과 Hit는 같이 될 수 없음
	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation
		, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;


	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void NotifyActorEndOverlap(AActor* OtherActor) override;



private:
	double HP;

	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(Category = "PlayerAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<PlayerAnimationEx, UAnimMontage*> PlayerAnimations;
};
