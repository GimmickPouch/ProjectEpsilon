// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetMarker.h"
#include "Enemies/BaseEnemy.h"


ATargetMarker::ATargetMarker()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    _targetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMarker"));
    _targetMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATargetMarker::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ATargetMarker::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_target)
    {
        FVector targetBoundOrigin;
        FVector targetBoundExtent;
        _target->GetActorBounds(true, targetBoundOrigin, targetBoundExtent);

        FVector floatPosition = targetBoundOrigin + FVector(0, 0, targetBoundExtent.Z + kFloatHeightAboveTarget);
        SetActorLocation(floatPosition);
    }
}

void ATargetMarker::SetTarget(ABaseEnemy* newTarget)
{
    if (newTarget)
    {
        _target = newTarget;
    }
    else
    {
        // TODO destroy this target
    }
}
