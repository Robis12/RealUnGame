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
	// ��Ʈ�ѷ��� ���� ������ �� �̰��� ����.
	void OnPossess(APawn* _Mon);




};
