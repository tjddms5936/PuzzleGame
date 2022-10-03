// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API UServerRow : public UUserWidget
{
	GENERATED_BODY()


protected:
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UFUNCTION()
	void Setup(class UMainMenu* InParent, uint32 Inindex);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ServerBtn;

	UPROPERTY() // Garbage Collection 시스템에서 적절하게 처리됨. 즉, 우리가 원할 때 아니면 삭제되지 않음
	UMainMenu* Parent;
	
	uint32 index;

	UFUNCTION()
	void OnClicked();
};
