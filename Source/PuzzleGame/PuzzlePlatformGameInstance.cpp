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
	InputModeData.SetWidgetToFocus(MainMenu->TakeWidget()); // 매개변수 : 포커싱하고자 하는 위젯
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); 

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetShowMouseCursor(true);
	
	/*
	다음 강의에서 다음과 같은 오류 메시지가 표시되는 경우:
	LogPlayerController: 오류: InputMode:UIOnly - 포커스를 가질 수 없는 위젯 SObjectWidget [Widget.cpp(710)]에 포커스를 맞추려고 합니다!
	다음 코드 라인을 추가해 보세요.
	MainMenu->bIsFocusable = true;
	*/
	
}

void UPuzzlePlatformGameInstance::HostServer()
{
	// GetEngine() : GameInstance만의 메서드. 
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

