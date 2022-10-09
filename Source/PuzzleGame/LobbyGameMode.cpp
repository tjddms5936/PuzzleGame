// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "PuzzlePlatformGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	++NumberOfPlayers;
	if (NumberOfPlayers >= 3) {
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, FString::Printf(TEXT("Reached 3 players!")));
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ALobbyGameMode::StartGame, 5);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	--NumberOfPlayers;
}

void ALobbyGameMode::StartGame()
{
	UPuzzlePlatformGameInstance* PuzzleGameInstance = Cast<UPuzzlePlatformGameInstance>(GetGameInstance());
	if (PuzzleGameInstance) {
		PuzzleGameInstance->StartSession();
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;

		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/Maps/Game?listen");
	}
}
