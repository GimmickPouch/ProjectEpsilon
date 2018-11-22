// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetMarker.generated.h"

UCLASS()
class PROJECTEPSILON_API ATargetMarker : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    ATargetMarker();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void SetTarget(class ABaseEnemy* newTarget);

    // Variables
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        UStaticMeshComponent* _targetMesh;

    class ABaseEnemy* _target;

private:
    const float kFloatHeightAboveTarget = 20.f;
    
};
