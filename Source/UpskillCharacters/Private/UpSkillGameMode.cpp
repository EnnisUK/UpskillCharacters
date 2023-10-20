// Fill out your copyright notice in the Description page of Project Settings.


#include "UpSkillGameMode.h"
#include "UObject/ConstructorHelpers.h"

AUpSkillGameMode::AUpSkillGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/bp_Character_Hook"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}