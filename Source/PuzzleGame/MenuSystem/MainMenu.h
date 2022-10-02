// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:
	
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FString> ServerNames);

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
	class UButton* JoinMenu_CancelBtn;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenu_JoinBtn; 

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerScrollBox;

	UFUNCTION()
	void HostServer(); // HostBtn

	UFUNCTION()
	void OpenJoinMenu(); // JoinBtn

	UFUNCTION()
	void JoinServer(); // JoinMenu_JoinBtn

	UFUNCTION()
	void JoinMenuCancel(); // JoinMenu_CancelBtn

	UFUNCTION()
	void ExitGame(); // ExitBtn

	UFUNCTION()
	void SelectIndex(uint32 index);

	TSubclassOf <class UUserWidget> ServerRowClass;

	// 음수와 32부분 이상의 정수를 요하지 않으므로 uint32 사용
	// TOptional의 좋은 점을 얻은 값이 null 값이 될 수도 있다는 것을 상기시켜줌
	TOptional<uint32> SelectedIndex;
};
