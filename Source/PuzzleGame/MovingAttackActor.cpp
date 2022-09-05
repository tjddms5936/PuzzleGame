// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingAttackActor.h"

// Sets default values
AMovingAttackActor::AMovingAttackActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingAttackActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingAttackActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

