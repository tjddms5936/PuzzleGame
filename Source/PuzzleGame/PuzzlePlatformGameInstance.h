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

	virtual void Init(); // BeginPlay 느낌

	UFUNCTION(Exec) // Exec : 이 기능은 게임 내 콘솔에서 실행할 수 있습니다. Exec 명령은 특정 클래스 내에서 선언된 경우에만 작동합니다.
	void HostServer();

	UFUNCTION(Exec)
	void Join(const FString& Address);
};
