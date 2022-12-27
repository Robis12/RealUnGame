// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RealUnAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API URealUnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	URealUnAnimInstance();

	void AddAnimMontage(int _Key, UAnimMontage* _Montage);

	template<typename EnumType>
	void SetDefaultMontage(EnumType _Key)
	{
		SetDefaultMontage(static_cast<int>(_Key));
	}

	void SetDefaultMontage(int _Key);

	void ChangeAnimMontage(int _Key, bool _Force = false);
	template<typename EnumType>
	void ChangeAnimMontage(EnumType _Key, bool _Force = false)
	{
		ChangeAnimMontage(static_cast<int>(_Key), _Force);
	}




	FORCEINLINE bool IsAnimMontage(int _Key)
	{
		return CurrentAnimationKey == _Key;
	}
	template<typename EnumType>
	bool IsAnimMontage(EnumType _Key)
	{
		return IsAnimMontage(static_cast<int>(_Key));
	}



	UAnimMontage* GetAnimation(int _Key);

	template<typename EnumType>
	UAnimMontage* GetAnimation(EnumType _Key)
	{
		return GetAnimation(static_cast<int>(_Key));
	}


	UAnimMontage* GetCurrentSelectMontage()
	{
		UAnimMontage** Anim = Animations.Find(CurrentAnimationKey);

		if (nullptr == Anim)
		{
			return nullptr;
		}

		return *Anim;
	}


private:
	UPROPERTY(Category = "AnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<int, UAnimMontage*> Animations;

	int CurrentAnimationKey;

	int DefaultKey;

	float Time;

protected:
	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;
};
