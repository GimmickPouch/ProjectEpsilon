// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EClassType : uint8
{
    CC_MeleeSword       UMETA(DisplayName = "Knight"),
    CC_RangedBow        UMETA(DisplayName = "Archer"),
    CC_MageDamage       UMETA(DisplayName = "Sorceror"),
    CC_MageHeal         UMETA(DisplayName = "Cleric"),
    CC_Summoner         UMETA(DisplayName = "Summoner"),
};