// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnAICharacter.h"
#include "RealUnAIController.h"
#include "Kismet/GamePlayStatics.h"

ARealUnAICharacter::ARealUnAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::Spawned;	

}

void ARealUnAICharacter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	
	
}
