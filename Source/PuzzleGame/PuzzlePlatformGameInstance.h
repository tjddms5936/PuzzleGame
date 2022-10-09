// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init(); // BeginPlay 느낌

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec, BlueprintCallable) // Exec : 이 기능은 게임 내 콘솔에서 실행할 수 있습니다. Exec 명령은 특정 클래스 내에서 선언된 경우에만 작동합니다.
	void HostServer(FString ServerName);

	UFUNCTION(Exec, BlueprintCallable)
	void Join(int index);

	UFUNCTION(Exec, BlueprintCallable)
	void LoadCancelMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void CancelMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void QuitMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void ExitGameFunc();

	UFUNCTION(Exec, BlueprintCallable)
	bool CallBackBool(bool input);

	UFUNCTION()
	void StartSession();

private:
	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> CancelMenuClass;

	class UMainMenu* MainMenu;

	FString DesiredServerName;


	// ==================== 온라인 세션 관련 =======================
	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearchPtr; // Default 값으로 nullptr을 가리킨다.



	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString = TEXT(""));

	void CreateSession();


	bool For_CallBackBool = false;

	void ServerListRefresh();
};
