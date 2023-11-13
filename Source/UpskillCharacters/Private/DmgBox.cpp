// Fill out your copyright notice in the Description page of Project Settings.


#include "DmgBox.h"
#include "GameFramework/Pawn.h"


// Sets default values
ADmgBox::ADmgBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");

}

// Called when the game starts or when spawned
void ADmgBox::BeginPlay()
{
	Super::BeginPlay();
	
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ADmgBox::OnBoxOverlap);
	



}

void ADmgBox::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABuffCharacter>(OtherActor))
	{
		TSubclassOf<UDamageType> DamageType;
		UGameplayStatics::ApplyDamage(OtherActor, 15, GetInstigatorController(), this, DamageType);
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Black, TEXT("BuffCharacter"));
		ABuffCharacter* BuffCharRef = Cast<ABuffCharacter>(OtherActor);
		BuffCharRef->CheckBuff();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Black, TEXT("Not BuffCharacter"));
	}
}

// Called every frame
void ADmgBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

