// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {

	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

	speed = 5;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		SetReplicates(true); // 이 액터가 네트워크 클라이언트에 복제할지 여부를 설정합니다.
		SetReplicateMovement(true); // 이 액터의 움직임이 네트워크 클라이언트에 복제되는지 여부를 설정합니다.
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); // 로컬위치 -> 글로벌 위치로 변환
	GlobalStartToTargetLengh = (GlobalTargetLocation - GlobalStartLocation).Size();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) {
		// 만약 서버라면?             flase라면 클라이언트 의미
		FVector location = GetActorLocation();
		float locationToTargeLength = (location - GlobalStartLocation).Size();
		if (locationToTargeLength > GlobalStartToTargetLengh) {
			// 목표지점을 지나친거임.
			FVector tmp = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = tmp;
		}

		// 방향을 정규화 하는 작업
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal(); // .Normal은 벡터자체를 수정. .GetSafeNormal은 벡터자체는 냅둠. unsafe? 부동소주점같은 작은 수 계산x
		
		location += speed * DeltaTime * Direction;
	
		/*
		float에 벡터를 곱하면 해당 방향의 크기가 증가.
		또는 화살표의 크기에서 벡터의 크기를 곱하기도 한다. 화살표의 크기가 1인 경우,
		기본적으로 그 방향을 사용하면서 크기를 늘리는 것과 같다. 
		그 늘어난 크리는 속도에 DeltaTime을 곱한 값과 같다. 
		*/
		SetActorLocation(location);
	}
}
