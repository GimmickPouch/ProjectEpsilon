// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums/CharacterEnums.h"
#include "ProjectEpsilonCharacter.generated.h"

UCLASS(config=Game)
class AProjectEpsilonCharacter : public ACharacter
{
    GENERATED_BODY()

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;
public:
    AProjectEpsilonCharacter();

    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
    float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
    float BaseLookUpRate;

protected:

    /** Resets HMD orientation in VR. */
    void OnResetVR();

    /** Called for forwards/backward input */
    void MoveForward(float Value);

    /** Called for side to side input */
    void MoveRight(float Value);

    /** 
     * Called via input to turn at a given rate. 
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void TurnAtRate(float Rate);

    /**
     * Called via input to turn look up/down at a given rate. 
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void LookUpAtRate(float Rate);

    /** Handler for when a touch input begins. */
    void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

    /** Handler for when a touch input stops. */
    void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
    // APawn interface
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    // End of APawn interface

public:
    ///** Returns CameraBoom subobject **/
    //FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    ///** Returns FollowCamera subobject **/
    //FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    // Luke from here
protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;

    // Attacking
    void PrimaryAttack();
    void EndPrimaryAttackCombo();

    void SecondarySkills();

    // Targeting
    void LockOnTargetToggle();
    void TargetNewEnemy();
    void CleanTargetHistory(bool forceClearAll = false);
    void SetCurrentTarget(class ABaseEnemy* enemy);
    void SpawnNewTargetMarker();

protected:
    // Character Class
    EClassType _currentClass;

    // Attacking
    bool _canAttack;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations)
    class UAnimMontage* _primaryAttackAnimation;

    class UBaseSkill* _primarySkill;

    // Targeting
    const float kMaxTargetRange = 20000.f;

    class ABaseEnemy* _currentTarget;

    class ATargetMarker* _targetMarker;
    TArray<TWeakObjectPtr<class ABaseEnemy>> _targetHistory;

    // Blueprints
private:
    UClass* _bpTargetMarker;
};

