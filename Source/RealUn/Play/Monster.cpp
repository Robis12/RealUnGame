// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Global/RealUnBlueprintFunctionLibrary.h"
#include "RealUn/Play/RealUnMonsterController.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RealUn/Global/RealUnStructs.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"



AMonster::AMonster()
{
	AIControllerClass = ARealUnMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	{
		UCapsuleComponent* Com = FindComponentByClass<UCapsuleComponent>();
		if (nullptr != Com)
		{
			Com->SetCollisionProfileName(FName(TEXT("Monster")));
		}

		RootComponent = Com;
	}

	{
		// CDO
		DamageCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Damage Collision")));
		DamageCollision->SetCollisionProfileName("MonsterAttack");
		DamageCollision->SetupAttachment(GetMesh(), FName(TEXT("RealUn_DamagePoint")));

		
	}

	{
		IconArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("SpringArmComp")));
		IconArm->SetupAttachment(RootComponent);
		IconArm->SetRelativeRotation(FRotator(-90., 0., 0.));
		
		IconArm->TargetArmLength = 300.f;
		IconArm->bInheritYaw = false;
		IconArm->bInheritPitch = false;
		IconArm->bInheritRoll = false;

		
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MatPath(TEXT("Material'/Game/Resources/Play/Sprite/UI/MiniMap/MonsterIcon_Mat.MonsterIcon_Mat'"));
		
		Plane = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("IconPlane")));
		Plane->SetupAttachment(IconArm);
		Plane->SetRelativeRotation(FRotator(0., 90., 90.));


		if (nullptr != MeshPath.Object
			&& MeshPath.Object->IsValidLowLevel())
		{
			Plane->SetStaticMesh(MeshPath.Object);
		}

		if (nullptr != MatPath.Object
			&& MatPath.Object->IsValidLowLevel())
		{
			Plane->SetMaterial(0, MatPath.Object);
		}

		
		Plane->bVisibleInSceneCaptureOnly = true;
		Plane->CastShadow = false;
		
		
	}



	Tags.Add("Monster");
}


void AMonster::BeginPlay()
{
	Super::BeginPlay();
	DamageOff();

	URealUnGameInstance* Instance = GetWorld()->GetGameInstance<URealUnGameInstance>();
	if (nullptr == Instance
		|| false == Instance->IsValidLowLevel())
	{
		return;
	}

	int32 Data = Instance->GetRandomStream().RandRange(3, 3);

	DropTable = Instance->GetRandomDropData(Data);


}



const FRealUnMonsterInfo* AMonster::MonsterDataInit()
{
	FString Name = GetClass()->GetName();
	Name = Name.Replace(TEXT("_C"), TEXT(""));

	MonsterData = URealUnBlueprintFunctionLibrary::GetRealUnInstance()->GetMonsterData(FName(*Name));

	if (nullptr == MonsterData)
	{
		UE_LOG(LogTemp, Error, TEXT("MonsterData Empty!"));
		return nullptr;
	}

	SetAnimations(MonsterData->Animations);

	SetHP(MonsterData->Hp);

	return MonsterData;
}



void AMonster::DamageOn()
{
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	TArray<FHitResult> Targets = CollsionCheck(DamageCollision->GetComponentLocation(), FName(TEXT("MonsterAttackTrace")), DamageCollision->GetCollisionShape());
	
	bool Check = false;

	for (size_t i = 0; i < Targets.Num(); ++i)
	{
		ARealUnCharacter* RealUn = Cast<ARealUnCharacter>(Targets[i].GetActor());
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
	DrawDebugSphere(GetWorld(), DamageCollision->GetComponentLocation(), DamageCollision->GetScaledSphereRadius(), 10, Color, false, 0.1f);
}

void AMonster::DamageOff()
{
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMonster::CalDamage(double _Damage)
{
	Super::CalDamage(_Damage);

	if (IsDeath())
	{
		ItemDrop(DropTable);
		/*for (size_t i = 0; i < length; i++)
		{

		}*/


		Destroy();
	}
}

