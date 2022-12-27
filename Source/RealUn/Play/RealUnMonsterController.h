// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/RealUnAIController.h"
#include "RealUnMonsterController.generated.h"

/**
 * 
 */
UCLASS()
class REALUN_API ARealUnMonsterController : public ARealUnAIController
{
	GENERATED_BODY()
	
public:
	//ARealUnMonsterController();
	//~ARealUnMonsterController();


protected:
	// 컨트롤러가 폰에 빙의할 때 이것이 사용됨.
	void OnPossess(APawn* _Mon);




};
