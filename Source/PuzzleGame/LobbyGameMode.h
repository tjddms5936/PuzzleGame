// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleGameGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API ALobbyGameMode : public APuzzleGameGameMode
{
	GENERATED_BODY()

public:

	// ���� override�� �ٿ��ָ�, �θ�κ��� ���� �Լ��� ������ �Ѵٴ� Ȯ���� ǥ���̴�.
	// �� �տ� virtual ��� override������ �ڵ����� ������ �ȴ�.
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;
	
private:
	uint32 NumberOfPlayers = 0;

	void StartGame();

	FTimerHandle TimerHandle;
};
