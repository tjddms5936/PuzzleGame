// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
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
	void Join(const FString& Address);

	UFUNCTION(Exec, BlueprintCallable)
	void LoadCancelMenu();

private:
	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> CancelMenuClass;

	class UMainMenu* MainMenu;
};
