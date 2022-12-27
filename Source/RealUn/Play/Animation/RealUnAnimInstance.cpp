// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnAnimInstance.h"


URealUnAnimInstance::URealUnAnimInstance()
{
	int a = 0;
}



// Animation Inst가 만들어졌을 때 실행
void URealUnAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

// Animation Inst가 동작중이면 계속 실행.
void URealUnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	UAnimMontage* FindMontage = GetAnimation(CurrentAnimationKey);
	if (nullptr == FindMontage)
	{
		return;
	}

	float Len = FindMontage->GetPlayLength();
	float Pos = Montage_GetPosition(FindMontage);
	Time += DeltaSeconds;

	float Percent = Time / Len;

	if (1.0f <= Percent)
	{
		CurrentAnimationKey = DefaultKey;
		ChangeAnimMontage(DefaultKey, true);
	}

	UE_LOG(LogTemp, Error, TEXT("Update Animation Len : [%f], Pos : [%f], Time : [%f]"), Len, Pos, Time);
}


void URealUnAnimInstance::AddAnimMontage(int _Key, UAnimMontage* _Montage)
{
	// 내부의 인자값을 *를 넘겨주게 됨.
	if (true == Animations.Contains(_Key))
	{
		UE_LOG(LogTemp, Error, TEXT("animation instance error!"));

		return;
	}

	Animations.Add(_Key, _Montage);
}

void URealUnAnimInstance::SetDefaultMontage(int _Key)
{
	DefaultKey = _Key;
}

void URealUnAnimInstance::ChangeAnimMontage(int _Key, bool _Force/* = false*/)
{
	UAnimMontage* FindMontage = GetAnimation(_Key);

	float Len = FindMontage->GetPlayLength();
	float Pos = Montage_GetPosition(FindMontage);


	// UE_LOG(LogTemp, Error, TEXT("Change Animation Len : [%f], Pos : [%f]"), Len, Pos);




	// 찾은 몽타주가 재생되고 있는지??
	if (false == Montage_IsPlaying(FindMontage) || true == _Force)
	{
		Time = 0.0f;
		// 1.3초면 1.3초 들어옴
		Montage_Play(FindMontage);
		CurrentAnimationKey = _Key;
	}
}

UAnimMontage* URealUnAnimInstance::GetAnimation(int _Key)
{
	UAnimMontage** FindMontage = Animations.Find(_Key);

	// UE_LOG(LogTemp, Error, TEXT("animation Montage Null!"));

	if (nullptr == FindMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("animation Montage Null!"));
		return nullptr;
	}

	return *FindMontage;
}
