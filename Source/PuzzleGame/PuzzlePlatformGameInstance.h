// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API UPuzzlePlatformGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init(); // BeginPlay ����

	UFUNCTION(Exec) // Exec : �� ����� ���� �� �ֿܼ��� ������ �� �ֽ��ϴ�. Exec ����� Ư�� Ŭ���� ������ ����� ��쿡�� �۵��մϴ�.
	void HostServer();

	UFUNCTION(Exec)
	void Join(const FString& Address);
};
