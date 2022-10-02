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

	// ������ 32�κ� �̻��� ������ ������ �����Ƿ� uint32 ���
	// TOptional�� ���� ���� ���� ���� null ���� �� ���� �ִٴ� ���� ��������
	TOptional<uint32> SelectedIndex;
};
