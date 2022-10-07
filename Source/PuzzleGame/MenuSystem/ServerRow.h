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
	virtual bool Initialize();

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HostName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerNum;

	UFUNCTION()
	void Setup(class UMainMenu* InParent, uint32 Inindex);

	UPROPERTY(BlueprintReadOnly)
	bool IsSelected = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Setting")
	bool IsTitle = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Setting")
	int32 TextSize = 15;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ServerBtn;

	UPROPERTY() // Garbage Collection �ý��ۿ��� �����ϰ� ó����. ��, �츮�� ���� �� �ƴϸ� �������� ����
	UMainMenu* Parent;
	
	uint32 index;

	UFUNCTION()
	void OnClicked();

};
