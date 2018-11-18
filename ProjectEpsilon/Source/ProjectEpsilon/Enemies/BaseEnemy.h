// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS()
class PROJECTEPSILON_API ABaseEnemy : public ACharacter
{
    GENERATED_BODY()

public:
    ABaseEnemy();

protected:
    virtual void BeginPlay() override;

public:	
    virtual void Tick(float DeltaTime) override;

    // Variables
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class UBoxComponent* _hitBox;

private:
    bool _canTarget;
    
};
