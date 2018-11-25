// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectEpsilonCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Enemies/BaseEnemy.h"
#include "EngineUtils.h"
#include "CombatClasses/CombatClassUtils.h"
#include "Combat/TargetMarker.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

//////////////////////////////////////////////////////////////////////////
// AProjectEpsilonCharacter

AProjectEpsilonCharacter::AProjectEpsilonCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    //// Create a camera boom (pulls in towards the player if there is a collision)
    //CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    //CameraBoom->SetupAttachment(RootComponent);
    //CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
    //CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    //// Create a follow camera
    //FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    //FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    //FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
    // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

    // Luke from here
    static ConstructorHelpers::FObjectFinder<UClass> targetBlueprint(TEXT("Class'/Game/Blueprints/Combat/TargetMarker.TargetMarker_C'"));
    if (targetBlueprint.Object)
    {
        _bpTargetMarker = targetBlueprint.Object;
    }
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectEpsilonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Set up gameplay key bindings
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAxis("MoveForward", this, &AProjectEpsilonCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AProjectEpsilonCharacter::MoveRight);

    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &AProjectEpsilonCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &AProjectEpsilonCharacter::LookUpAtRate);

    // handle touch devices
    PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjectEpsilonCharacter::TouchStarted);
    PlayerInputComponent->BindTouch(IE_Released, this, &AProjectEpsilonCharacter::TouchStopped);

    // VR headset functionality
    PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AProjectEpsilonCharacter::OnResetVR);

    // Luke additions
    PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &AProjectEpsilonCharacter::LockOnTargetToggle);
}


void AProjectEpsilonCharacter::OnResetVR()
{
    UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AProjectEpsilonCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
        Jump();
}

void AProjectEpsilonCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
        StopJumping();
}

void AProjectEpsilonCharacter::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProjectEpsilonCharacter::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AProjectEpsilonCharacter::MoveForward(float Value)
{
    if ((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AProjectEpsilonCharacter::MoveRight(float Value)
{
    if ( (Controller != NULL) && (Value != 0.0f) )
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
    
        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

// Luke from here

void AProjectEpsilonCharacter::Tick(float DeltaSeconds)
{
    if (_currentTarget)
    {
        FVector lineToTarget = _currentTarget->GetActorLocation() - GetActorLocation();
        FRotator rotationToTarget = FRotationMatrix::MakeFromX(lineToTarget).Rotator();
        rotationToTarget.Pitch = 0.f;
        SetActorRotation(rotationToTarget);
    }
}

void AProjectEpsilonCharacter::LockOnTargetToggle()
{
    TargetNewEnemy();
}

void AProjectEpsilonCharacter::TargetNewEnemy()
{
    CleanTargetHistory();

    ABaseEnemy* closestEnemy = nullptr;
    float shortestDistance = kMaxTargetRange;
    for (TActorIterator<ABaseEnemy> actorItr(GetWorld()); actorItr; ++actorItr)
    {
        if (*actorItr && !(_targetHistory.Num() > 0 && _targetHistory.Contains(*actorItr)))
        {
            float distanceToEnemy = GetDistanceTo(*actorItr);
            if (distanceToEnemy < shortestDistance)
            {
                closestEnemy = *actorItr;
                shortestDistance = distanceToEnemy;
            }
        }
    }

    if (closestEnemy != nullptr || _currentTarget != nullptr)
    {
        SetCurrentTarget(closestEnemy);
    }
}

void AProjectEpsilonCharacter::CleanTargetHistory(bool forceClearAll)
{
    if (forceClearAll)
    {
        _targetHistory.Empty();
    }
    else if (_targetHistory.Num() > 0)
    {
        for (int i = _targetHistory.Num() - 1; i >= 0; --i)
        {
            if (!_targetHistory[i].IsValid())
            {
                _targetHistory.RemoveAt(i);
            }
        }
    }
}

void AProjectEpsilonCharacter::SetCurrentTarget(ABaseEnemy* enemy)
{
    if (enemy)
    {
        _currentTarget = enemy;
        _targetHistory.Add(enemy);
        if (_bpTargetMarker)
        {
            if (!_targetMarker)
            {
                SpawnNewTargetMarker();
            }
            _targetMarker->SetTarget(_currentTarget);
        }
    }
    else
    {
        _currentTarget = nullptr;
    }

    if (_currentTarget == nullptr && _targetMarker)
    {
        _targetMarker->Destroy();
        _targetMarker = nullptr;
        CleanTargetHistory(true);
    }
}

void AProjectEpsilonCharacter::SpawnNewTargetMarker()
{
    if (_bpTargetMarker)
    {
        FVector location (0.0f, 0.0f, 0.0f);
        FRotator rotation (0.0f, 0.0f, 0.0f);
        FActorSpawnParameters spawnInfo;
        _targetMarker = GetWorld()->SpawnActor<ATargetMarker>(_bpTargetMarker, location, rotation, spawnInfo);
    }
}
