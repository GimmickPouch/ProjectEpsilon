// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillEffectZone.generated.h"

UCLASS()
class PROJECTEPSILON_API ASkillEffectZone : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    ASkillEffectZone();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    
    // Variables
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        UStaticMeshComponent* _zoneMarker;
};
