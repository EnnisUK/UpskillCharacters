// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Character_Hook.h"

// Sets default values
ACharacter_Hook::ACharacter_Hook()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacter_Hook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Hook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Hook::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

