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
	

protected:
	virtual bool Initialize();


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinBtn;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;


	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenu_CancelBtn;


	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenu_JoinBtn;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* IPAdressField;

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void JoinMenuCancel();

};
