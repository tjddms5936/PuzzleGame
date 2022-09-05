// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

public:
	// Method
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Activate();

	void DeActivate();

public:
	// Variables
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom System")
	float speed;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true), Category = "Custom System")
	FVector TargetLocation;
	
	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category =  "Custom System")
	bool IsActivateMoving;
private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	float GlobalStartToTargetLengh;


};
