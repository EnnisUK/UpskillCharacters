// Fill out your copyright notice in the Description page of Project Settings.


#include "Environments/SpikeWall.h"

// Sets default values
ASpikeWall::ASpikeWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_wallMesh = CreateDefaultSubobject<UStaticMeshComponent>("WallMesh");
	RootComponent = m_wallMesh;
	m_spikeMesh = CreateDefaultSubobject<UStaticMeshComponent>("SpikeMesh");
	m_spikeMesh->SetGenerateOverlapEvents(true);
	m_spikeMesh->SetupAttachment(GetRootComponent());
}


// Called when the game starts or when spawned
void ASpikeWall::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASpikeWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpikeWall::SpikeHitPlayer()
{
}
