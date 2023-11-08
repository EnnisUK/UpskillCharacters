// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DashCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Containers/EnumAsByte.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"



// Sets default values
ADashCharacter::ADashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
}

void ADashCharacter::DashAbility()
{
	
	FCollisionResponseParams ResponseParams;
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	QueryParams.AddIgnoredActor(this);
	FHitResult Hit;
	const FVector StartTrace = GetFollowCamera()->GetComponentLocation();
	FRotator CurrentRotation = GetFollowCamera()->GetComponentRotation();
	FVector EndTrace = StartTrace + CurrentRotation.Vector() * TeleportDistance;

	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECollisionChannel::ECC_Camera, QueryParams, ResponseParams);

		if (!HasDash)
		{
			LaunchCharacter(FVector(0,0,100), false, false);
			GetMesh()->SetMaterial(0, InvisMaterial);
			GetMesh()->SetMaterial(1, InvisMaterial);
			SetActorLocation(FMath::Lerp(GetActorLocation(), EndTrace, 1.0f), true);
			HasDash = true;
			FTimerHandle DashHandle;
			FTimerHandle InvisHandle;
			GetWorldTimerManager().SetTimer(DashHandle, this, &ADashCharacter::ResetDash, 1.0f, false);
			GetWorldTimerManager().SetTimer(InvisHandle, this, &ADashCharacter::ResetInvis, 3.0f, false);
			

			if (DashEffect)
			{
				UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DashEffect, GetActorLocation(), GetMesh()->GetSocketRotation(FName("DashEffect")));
			}


		}

		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Orange, true);

}

void ADashCharacter::ResetDash()
{

	HasDash = false;
	
}

void ADashCharacter::ResetInvis()
{
	GetMesh()->SetMaterial(0, Element1Mat);
	GetMesh()->SetMaterial(1, Element2Mat);
}



// Called when the game starts or when spawned
void ADashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADashCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADashCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
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



// Called every frame
void ADashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ADashCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ADashCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	//Ability
	PlayerInputComponent->BindAction("Ability", IE_Pressed, this, &ADashCharacter::DashAbility);


}

