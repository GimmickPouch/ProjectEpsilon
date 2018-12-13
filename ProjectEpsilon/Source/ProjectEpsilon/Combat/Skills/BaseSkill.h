// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseSkill.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PROJECTEPSILON_API UBaseSkill : public UObject
{
    GENERATED_BODY()

public:
    UBaseSkill();
    ~UBaseSkill();

    // Variables
protected:
    float _damage;

    // Getters and Setters
public:
    float GetDamage() const { return _damage; };
    void SetDamage(float value) { _damage = value; };
};
