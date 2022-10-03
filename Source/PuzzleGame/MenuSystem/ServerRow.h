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

	UPROPERTY() // Garbage Collection �ý��ۿ��� �����ϰ� ó����. ��, �츮�� ���� �� �ƴϸ� �������� ����
	UMainMenu* Parent;
	
	uint32 index;

	UFUNCTION()
	void OnClicked();
};
