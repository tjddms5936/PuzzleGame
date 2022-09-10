// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"


UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer) 
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UserWidgetWBPClass(TEXT("/Game/MenuSystem/WBP_Menu"));
	if (!ensure(UserWidgetWBPClass.Class != nullptr)) return;

	MenuClass = UserWidgetWBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	UUserWidget* MainMenu = CreateWidget<UUserWidget>(this, MenuClass, FName(MenuClass->GetName()));

	if (!ensure(MainMenu != nullptr)) return;
	MainMenu->AddToViewport();
	MainMenu->bIsFocusable = true;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(MainMenu->TakeWidget()); // �Ű����� : ��Ŀ���ϰ��� �ϴ� ����
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); 

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetShowMouseCursor(true);
	
	/*
	���� ���ǿ��� ������ ���� ���� �޽����� ǥ�õǴ� ���:
	LogPlayerController: ����: InputMode:UIOnly - ��Ŀ���� ���� �� ���� ���� SObjectWidget [Widget.cpp(710)]�� ��Ŀ���� ���߷��� �մϴ�!
	���� �ڵ� ������ �߰��� ������.
	MainMenu->bIsFocusable = true;
	*/
	
}

void UPuzzlePlatformGameInstance::HostServer()
{
	// GetEngine() : GameInstance���� �޼���. 
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Green, TEXT("Hosting"));
	
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Black, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(*Address, ETravelType::TRAVEL_Absolute);
}

