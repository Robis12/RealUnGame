// Fill out your copyright notice in the Description page of Project Settings.


#include "RealUnCharacter.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/ShapeComponent.h"

#include "RealUn/Play/RealUnStaticMeshActor.h"
#include "RealUn/Play/RealUnItemActor.h"
#include "RealUn/Global/RealUnGameInstance.h"
#include "RealUn/Play/RealUnStaticMeshActor.h"

// Sets default values
ARealUnCharacter::ARealUnCharacter()
	: IsAttackCheck(false)
	, Path(nullptr)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("RealUnCharacter");
}



// Called when the game starts or when spawned
void ARealUnCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AnimationInst = Cast<URealUnAnimInstance>(GetMesh()->GetAnimInstance());

	if (nullptr == AnimationInst
		|| false == AnimationInst->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("animation instance error!"));
		return;
	}

	if (true == Animations.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Animations Empty!"));
		return;
	}

	for (auto& Anim : Animations)
	{
		GetAnimationInst()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}


	GetAnimationInst()->SetDefaultMontage(DefaultAnimation::Idle);

	AnimationInst->ChangeAnimMontage(DefaultAnimation::Idle);

	// 미니맵에서 안찍히게 설정
	GetMesh()->bHiddenInSceneCapture = true;
}

// Called every frame
void ARealUnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARealUnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



AActor* ARealUnCharacter::TargetSearch(FName _Name, float _Range/* = -1.f*/)
{
	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), _Name, Actors);


	if (Actors.IsEmpty())
	{
		return nullptr;
	}


	if (0.f >= _Range)
	{
		return Actors[0];
	}


	FVector Location = GetActorLocation();

	for (size_t i = 0; i < Actors.Num(); i++)
	{
		float Len = (Location - Actors[i]->GetActorLocation()).Size();

		if (_Range > Len)
		{
			return Actors[i];
		}

	}


	return nullptr;
}

bool ARealUnCharacter::GetIsRangeInTarget(AActor* _Target, float _Len)
{
	return GetTargetDir(_Target).Size() <= _Len;
}

FVector ARealUnCharacter::GetTargetDir(AActor* _Target)
{
	return _Target->GetActorLocation() - GetActorLocation();
}

FVector ARealUnCharacter::GetTargetDir(const FVector& _TargetLocation)
{
	return _TargetLocation - GetActorLocation();
}

void ARealUnCharacter::SetTargetMovementInput(AActor* _Target, float Value /*= 1.0f*/)
{
	SetDirMovementInput(GetTargetDirNormal(_Target), Value);
}

void ARealUnCharacter::SetDirMovementInput(FVector _Dir, float Value)
{
	AddMovementInput(_Dir.GetSafeNormal(), Value);
}

FVector ARealUnCharacter::GetTargetDirNormal(AActor* _Target)
{
	return GetTargetDir(_Target).GetSafeNormal();
}

FVector ARealUnCharacter::GetTargetDirNormal(const FVector& _TargetLocation)
{
	return GetTargetDir(_TargetLocation).GetSafeNormal();
}

void ARealUnCharacter::SetTargetLook(AActor* _Target)
{
	SetActorRotation(GetTargetDirNormal(_Target).Rotation());
}

void ARealUnCharacter::SetDirLook(FVector _Dir)
{
	FVector Forward = GetActorForwardVector() * 10.0f;

	_Dir = _Dir.GetSafeNormal();

	Forward.Z = 0.0f;

	_Dir += Forward;

	SetActorRotation(_Dir.GetSafeNormal().Rotation());
}

TArray<AActor*> ARealUnCharacter::TargetsSearch(FName _Name, float _Range/* = -1.f*/)
{
	TArray<AActor*> Actors;
	TArray<AActor*> SelectActors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), _Name, Actors);


	if (Actors.IsEmpty())
	{
		return Actors;
	}


	if (0.f >= _Range)
	{
		return Actors;
	}


	FVector Location = GetActorLocation();

	for (size_t i = 0; i < Actors.Num(); i++)
	{
		float Len = (Location - Actors[i]->GetActorLocation()).Size();

		if (_Range > Len)
		{
			SelectActors.Add(Actors[i]);
		}

	}


	return SelectActors;
}


void ARealUnCharacter::CalDamage(double _Damage)
{
	HP -= _Damage;
}

TArray<FHitResult> ARealUnCharacter::CollsionCheck(const FVector& Start, const FVector& End, const FQuat& Rot, FName ProfileName, const FCollisionShape& CollisionShape)
{
	FCollisionQueryParams CollisionQuery(FName(TEXT("CollisionCheck")), false, this);

	TArray<FHitResult> Result = TArray<FHitResult>();

	GetWorld()->SweepMultiByProfile(
		Result,
		Start,
		End,
		Rot,
		ProfileName,
		CollisionShape,
		CollisionQuery);


	return Result;

}

TArray<UActorComponent*> ARealUnCharacter::GetDamageCollision()
{
	return GetComponentsByTag(UShapeComponent::StaticClass(), FName(TEXT("Damage")));
}

void ARealUnCharacter::ItemDrop(const TArray<const struct FItemData*>& _Array)
{
	URealUnGameInstance* Instance = GetWorld()->GetGameInstance<URealUnGameInstance>();
	if (nullptr == Instance)
	{
		return;
	}

	TSubclassOf<UObject> Object = Instance->GetObjectData(FName(TEXT("Item")));

	for (size_t i = 0; i < _Array.Num(); i++)
	{
		FTransform SpawnTransform(GetActorLocation());

		ARealUnItemActor* NewActor = GetWorld()->SpawnActor<ARealUnItemActor>(Object, SpawnTransform);

		NewActor->SetItem(_Array[i]);
	}
}

UNavigationPath* ARealUnCharacter::PathFind(AActor* _Actor)
{
	if (nullptr == _Actor)
	{
		return nullptr;
	}

	return PathFind(_Actor->GetActorLocation());
}

UNavigationPath* ARealUnCharacter::PathFind(const FVector& _TargetPosition)
{
	return UNavigationSystemV1::FindPathToLocationSynchronously
	(
		GetWorld(), //UObject* WorldContextObject,
		GetActorLocation(), //const FVector & PathStart,
		_TargetPosition //const FVector& PathEnd,
		//float TetherDistance,
		//AActor* PathfindingContext,
		//TSubclassOf<UNavigationQueryFilter> FilterClass
	);
}

// false를 리턴하면 다시 탐색하든 직선으로 달리든
bool ARealUnCharacter::PathMove()
{
	if (nullptr == Path)
	{
		return false;
	}

	if (0 == Path->PathPoints.Num())
	{
		return false;
	}

	FVector TargetPos = Path->PathPoints[0];
	FVector ActorPos = GetActorLocation();

	ActorPos.Z = 0.0f;
	TargetPos.Z = 0.0f;

	FVector Dir = TargetPos - ActorPos;

	if (50.0f >= Dir.Size())
	{
		Path->PathPoints.RemoveAt(0);

		if (0 == Path->PathPoints.Num())
		{
			// 다시 Path를 찾아라 --> 다른 곳으로 이동할 곳이 없음.
			return false;
		}
		TargetPos = Path->PathPoints[0];
		TargetPos.Z = 0.0f;

		Dir = TargetPos - ActorPos;
	}
	

	SetDirLook(Dir);
	SetDirMovementInput(Dir);
	GetAnimationInst()->ChangeAnimMontage(DefaultAnimation::Forward);


	int a = 0;

	return true;
}

float ARealUnCharacter::GetLastPathPointToTargetDis(const FVector& _TargetPos)
{
	FVector LastPoint = Path->PathPoints.Last();
	FVector TargetPos = _TargetPos;

	LastPoint.Z = 0.0f;
	TargetPos.Z = 0.0f;

	return (LastPoint - TargetPos).Size();
}

void ARealUnCharacter::SetPath(UNavigationPath* _Path, bool _Debug /*= false*/)
{
	Path = _Path;

	if (false == _Debug)
	{
		return;
	}

	//
	FColor Color = FColor::Black;

	// Zero 디비전을 막기위해서
	float PathColor = 255 / (Path->PathPoints.Num() + 1);

	for (size_t i = 0; i < Path->PathPoints.Num() - 1; i++)
	{
		FVector Start = Path->PathPoints[i];
		FVector End = Path->PathPoints[i + 1];

		Color.R += PathColor;
		
		DrawDebugLine(GetWorld(), Start, End, Color, false, 1.0f, 0, 10.0f);
	}
}

void ARealUnCharacter::ResetPath()
{
	SetPath(nullptr);
}

float ARealUnCharacter::GetPercentHP()
{
	if (MaxHP <= 0.0)
	{
		return 0.0f;
	}

	return HP / MaxHP;
}

float ARealUnCharacter::GetPercentMP()
{
	if (MaxMP <= 0.0)
	{
		return 0.0f;
	}

	return MP / MaxMP;
}
