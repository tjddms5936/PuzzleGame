// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "CancelMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API UCancelMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize();
	
public:


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitBtn;

	UFUNCTION()
	void CancelMenuFunc();

	UFUNCTION()
	void QuitMenuFunc();
	
};
