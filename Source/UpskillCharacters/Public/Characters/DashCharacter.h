// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DashCharacter.generated.h"

class UNiagaraSystem;

UCLASS()
class UPSKILLCHARACTERS_API ADashCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	ADashCharacter();

	void DashAbility();

	void ResetDash();

	void ResetInvis();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SphereRadius = 200.f;

	bool HasDash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TeleportDistance;

	UPROPERTY(EditAnywhere, Category = "DashVFX")
	UNiagaraSystem* DashEffect;

	UPROPERTY(EditAnywhere, Category = "DashVFX")
	UMaterialInterface* InvisMaterial;

	UPROPERTY(EditAnywhere, Category = "DashVFX")
	UMaterialInterface* Element1Mat;

	UPROPERTY(EditAnywhere, Category = "DashVFX")
	UMaterialInterface* Element2Mat;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
