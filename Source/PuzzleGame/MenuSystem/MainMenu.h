// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

USTRUCT(BlueprintType)
struct FServerData
{
	GENERATED_BODY()

public:
	FServerData() {
		ServerName = "Null";
		CurrenctPlayers = 0;
		MaxPlayers = 0;
	}
	FString ServerName;
	uint16 CurrenctPlayers;
	uint16 MaxPlayers;
	FString HostUserName;

};

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:
	
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);

	UFUNCTION()
	void SelectIndex(uint32 index);

protected:
	virtual bool Initialize();


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitBtn;
	

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostMenu_HostBtn;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* ServerNameInput;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostMenu_CancelBtn;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenu_CancelBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenu_JoinBtn; 

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerScrollBox;

	UFUNCTION()
	void OpenHostMenu(); // HostBtn

	UFUNCTION()
	void HostServer(); // HostBtn

	UFUNCTION()
	void OpenJoinMenu(); // JoinBtn

	UFUNCTION()
	void JoinServer(); // JoinMenu_JoinBtn

	UFUNCTION()
	void MenuCancel(); // JoinMenu_CancelBtn, HostMenu_CancelBtn

	UFUNCTION()
	void ExitGame(); // ExitBtn

	UFUNCTION()
	void UpdateChildren();


	TSubclassOf <class UUserWidget> ServerRowClass;


	// 음수와 32부분 이상의 정수를 요하지 않으므로 uint32 사용
	// TOptional의 좋은 점을 얻은 값이 null 값이 될 수도 있다는 것을 상기시켜줌
	TOptional<uint32> SelectedIndex;
};
