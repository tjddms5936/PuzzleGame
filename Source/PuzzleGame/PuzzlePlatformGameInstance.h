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

	UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init(); // BeginPlay ����

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec, BlueprintCallable) // Exec : �� ����� ���� �� �ֿܼ��� ������ �� �ֽ��ϴ�. Exec ����� Ư�� Ŭ���� ������ ����� ��쿡�� �۵��մϴ�.
	void HostServer();

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

private:
	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> CancelMenuClass;

	class UMainMenu* MainMenu;


	// ==================== �¶��� ���� ���� =======================
	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearchPtr; // Default ������ nullptr�� ����Ų��.



	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void CreateSession();

	bool For_CallBackBool = false;

	void ServerListRefresh();
};
