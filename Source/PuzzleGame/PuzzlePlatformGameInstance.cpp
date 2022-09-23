// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem./MainMenu.h"
#include "MenuSystem/MenuWidget.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer) 
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UserWidgetWBPClass(TEXT("/Game/MenuSystem/WBP_Menu"));
	if (!ensure(UserWidgetWBPClass.Class != nullptr)) return;
	MenuClass = UserWidgetWBPClass.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> UserWidgetWBP_CancelMenuClass(TEXT("/Game/MenuSystem/WBP_CancelMenu"));
	if (!ensure(UserWidgetWBP_CancelMenuClass.Class != nullptr)) return;
	CancelMenuClass = UserWidgetWBP_CancelMenuClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *CancelMenuClass->GetName());
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	UMenuWidget* MainMenu_ = CreateWidget<UMenuWidget>(this, MenuClass, FName(MenuClass->GetName()));

	MainMenu_->Setup();

	MainMenu_->SetMenuInterface(this);
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

void UPuzzlePlatformGameInstance::LoadCancelMenu()
{
	if (!ensure(CancelMenuClass != nullptr)) return;
	UMenuWidget* CancelMenu = CreateWidget<UMenuWidget>(this, CancelMenuClass, FName(CancelMenuClass->GetName()));
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, FString::Printf(TEXT("CancelMenu Open")));
	CancelMenu->Setup();
	CancelMenu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::CancelMenu()
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, FString::Printf(TEXT("CancelMenu Clicked in GameInstance")));
}

void UPuzzlePlatformGameInstance::QuitMenu()
{
	UWorld* World = GetWorld();
	APlayerController* Controller = World->GetFirstPlayerController();
	if (!ensure(Controller != nullptr)) return;
	Controller->ClientTravel("/Game/Maps/Menu", ETravelType::TRAVEL_Absolute);

	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, FString::Printf(TEXT("QuitMenu Clicked in GameInstance")));
}

void UPuzzlePlatformGameInstance::ExitGameFunc()
{
	UWorld* World = GetWorld();
	APlayerController* Controller = World->GetFirstPlayerController();
	if (!ensure(Controller != nullptr)) return;

	// 게임 실행 후 콘솔창에 quit하면 게임이 꺼진다. 그걸 C++로 구현
	Controller->ConsoleCommand(FString("quit"));
}

