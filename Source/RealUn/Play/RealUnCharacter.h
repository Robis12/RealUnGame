// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RealUn/Global/RealUnEnum.h"
#include "Animation/RealUnAnimInstance.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "RealUnCharacter.generated.h"







UCLASS()
class REALUN_API ARealUnCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARealUnCharacter();

	FORCEINLINE URealUnAnimInstance* GetAnimationInst()
	{
		return AnimationInst;
	}

	virtual void DamageOn() { }

	virtual void DamageOff() { }

	bool GetIsRangeInTarget(AActor* _Target, float _Len);

	FVector GetTargetDir(AActor* _Target);
	FVector GetTargetDir(const FVector& _TargetLocation);


	void SetTargetMovementInput(AActor* _Target, float Value = 1.0f);

	void SetDirMovementInput(FVector _Dir, float Value = 1.0f);

	FVector GetTargetDirNormal(AActor* _Target);
	FVector GetTargetDirNormal(const FVector& _TargetLocation);

	void SetTargetLook(AActor* _Target);
	void SetDirLook(FVector _Dir);

	template<typename T>
	T* TargetSearch(FName _Name, float _Range = -1.f)
	{
		return Cast<T>(TargetSearch(_Name, _Range));
	}

	// Range 안에 있으면
	AActor* TargetSearch(FName _Name, float _Range = -1.f);
	TArray<AActor*> TargetsSearch(FName _Name, float _Range = -1.f);


	UFUNCTION(BlueprintCallable, Category = RealUn)
	virtual void CalDamage(double _Damage);

	FORCEINLINE void SetHP(double _HP) { HP = _HP; }
	FORCEINLINE double GetHP() { return HP; }
	FORCEINLINE bool IsDeath() { return HP <= 0.; }
	FORCEINLINE double GetMP() { return MP; }
	FORCEINLINE void SetMP(double _MP) { MP = _MP; }

	FORCEINLINE void SetAnimations(const TMap<DefaultAnimation, UAnimMontage*>& _Animations) 
	{
		Animations.Empty();
		Animations = _Animations; 
	}



	TArray<FHitResult> CollsionCheck(const FVector& Pos, FName ProfileName, const struct FCollisionShape& CollisionShape)
	{
		return CollsionCheck(Pos, Pos, FQuat::Identity, ProfileName, CollisionShape);
	}

	TArray<FHitResult> CollsionCheck(const FVector& Start, const FVector& End, const FQuat& Rot, FName ProfileName, const struct FCollisionShape& CollisionShape);

	TArray<UActorComponent*> GetDamageCollision();

	void ItemDrop(const TArray<const struct FItemData*>& _Array);

	UNavigationPath* PathFind(AActor* _Actor);

	UNavigationPath* PathFind(const FVector& _TargetPosition);

	bool PathMove();

	FORCEINLINE UNavigationPath* GetPath() { return Path; }
	FORCEINLINE FVector GetLastPathPoint() { return Path->PathPoints.Last(); }
	float GetLastPathPointToTargetDis(const FVector& TargetPos);

	void SetPath(UNavigationPath* _Path, bool _Debug = false);

	void ResetPath();

	UFUNCTION(BlueprintCallable, Category = RealUn)
	float GetPercentHP();
	UFUNCTION(BlueprintCallable, Category = RealUn)
	float GetPercentMP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	DefaultAnimation AnimationState;

private:
	bool IsAttackCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	double HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	double MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	double MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	double MaxMP;

	class URealUnAnimInstance* AnimationInst;

	UPROPERTY(Category = "AnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<DefaultAnimation, UAnimMontage*> Animations;

	class UNavigationPath* Path;
};
