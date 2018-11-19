// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCombatClass.generated.h"

UENUM(BlueprintType)
enum class EClassType : uint8
{
    CC_MeleeSword       UMETA(DisplayName = "Knight"),
    CC_RangedBow        UMETA(DisplayName = "Archer"),
    CC_MageDamage       UMETA(DisplayName = "Sorceror"),
    CC_MageHeal         UMETA(DisplayName = "Cleric"),
    CC_Summoner         UMETA(DisplayName = "Summoner"),
};

UCLASS(Blueprintable, BlueprintType)
class PROJECTEPSILON_API UBaseCombatClass : public UObject
{
    GENERATED_BODY()

public:
    UBaseCombatClass();
    ~UBaseCombatClass();

};