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
		SetReplicates(true); // �� ���Ͱ� ��Ʈ��ũ Ŭ���̾�Ʈ�� �������� ���θ� �����մϴ�.
		SetReplicateMovement(true); // �� ������ �������� ��Ʈ��ũ Ŭ���̾�Ʈ�� �����Ǵ��� ���θ� �����մϴ�.
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); // ������ġ -> �۷ι� ��ġ�� ��ȯ
	GlobalStartToTargetLengh = (GlobalTargetLocation - GlobalStartLocation).Size();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) {
		// ���� �������?             flase��� Ŭ���̾�Ʈ �ǹ�
		FVector location = GetActorLocation();
		float locationToTargeLength = (location - GlobalStartLocation).Size();
		if (locationToTargeLength > GlobalStartToTargetLengh) {
			// ��ǥ������ ����ģ����.
			FVector tmp = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = tmp;
		}

		// ������ ����ȭ �ϴ� �۾�
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal(); // .Normal�� ������ü�� ����. .GetSafeNormal�� ������ü�� ����. unsafe? �ε����������� ���� �� ���x
		
		location += speed * DeltaTime * Direction;
	
		/*
		float�� ���͸� ���ϸ� �ش� ������ ũ�Ⱑ ����.
		�Ǵ� ȭ��ǥ�� ũ�⿡�� ������ ũ�⸦ ���ϱ⵵ �Ѵ�. ȭ��ǥ�� ũ�Ⱑ 1�� ���,
		�⺻������ �� ������ ����ϸ鼭 ũ�⸦ �ø��� �Ͱ� ����. 
		�� �þ ũ���� �ӵ��� DeltaTime�� ���� ���� ����. 
		*/
		SetActorLocation(location);
	}
}
