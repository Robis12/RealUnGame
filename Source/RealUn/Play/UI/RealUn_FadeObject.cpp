// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUn_FadeObject.h"

float URealUn_FadeObject::ColorSetting(float _InDeltaTime)
{
	WaitTime -= _InDeltaTime;

	if (0.0f <= WaitTime)
	{
		return StartColor.A;
	}

	StartColor.A -= _InDeltaTime;

	return StartColor.A;
}

void URealUn_FadeObject::StartTimeSetting(float _WaitTime)
{
	WaitTime = _WaitTime;
	StartColor.A = 1.0f;
	
}
