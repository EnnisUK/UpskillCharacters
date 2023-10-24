// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpikeWall.generated.h"

UCLASS()
class UPSKILLCHARACTERS_API ASpikeWall : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_wallMesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_spikeMesh;
	
public:	
	// Sets default values for this actor's properties
	ASpikeWall();

	void SpikeHitPlayer();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float m_damageAmount;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
