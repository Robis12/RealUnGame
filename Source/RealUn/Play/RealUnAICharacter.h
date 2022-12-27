// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/RealUnCharacter.h"
#include "RealUnAICharacter.generated.h"



UCLASS()
class REALUN_API ARealUnAICharacter : public ARealUnCharacter
{
	GENERATED_BODY()

public:
	ARealUnAICharacter();
	
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	FORCEINLINE class UBlackboardData* GetBlackboardData() const { return BlackboardData; }


protected:
	void Tick(float _DeltaTime) override;



private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RealUn AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RealUn AI", meta = (AllowPrivateAccess = "true"))
	class UBlackboardData* BlackboardData;
};
