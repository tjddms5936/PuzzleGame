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

	// 끝에 override를 붙여주면, 부모로부터 받은 함수를 재정의 한다는 확실한 표현이다.
	// 맨 앞에 virtual 없어도 override때문에 자동으로 가상이 된다.
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;
	
private:
	uint32 NumberOfPlayers = 0;

	void StartGame();

	FTimerHandle TimerHandle;
};
