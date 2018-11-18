// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    _hitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
    _hitBox->SetCollisionProfileName("OverlapAll");
    _hitBox->SetCanEverAffectNavigation(false);
    _hitBox->bGenerateOverlapEvents = true;
    _hitBox->SetupAttachment(RootComponent);

    _canTarget = true;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
;}

