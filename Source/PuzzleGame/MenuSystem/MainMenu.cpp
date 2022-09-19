// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"


bool UMainMenu::Initialize() {
	bool Success = Super::Initialize(); // 혹시 Initialize가 false를 반환 할 수 있으므로
	if (!Success) return false; 

	// ToDo : SetUp
	if (ensure(HostBtn == nullptr)) return false;
	HostBtn->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (ensure(JoinBtn == nullptr)) return false;
	JoinBtn->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (ensure(JoinMenu_JoinBtn == nullptr)) return false;
	JoinMenu_JoinBtn->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (ensure(JoinMenu_CancelBtn == nullptr)) return false;
	JoinMenu_CancelBtn->OnClicked.AddDynamic(this, &UMainMenu::JoinMenuCancel);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr) {
		MenuInterface->HostServer(); // 순수가상함수 호출! 해당 함수는 어디서 구현되어 있을까?
		TearDown();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("MenuInterface == nullptr"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Host Server!!!"));
}

void UMainMenu::OpenJoinMenu()
{
	if (ensure(MenuSwitcher == nullptr)) return;
	if (ensure(JoinMenu == nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::JoinServer()
{
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Blue, FString::Printf(TEXT("Joining s")));

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	/*if (PlayerController) {
		PlayerController->ClientTravel()
	}*/
	return;
}

void UMainMenu::JoinMenuCancel()
{
	if (ensure(MenuSwitcher == nullptr)) return;
	if (ensure(MainMenu == nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface_)
{
	this->MenuInterface = MenuInterface_;
}

void UMainMenu::Setup()
{
	this->AddToViewport();
	this->bIsFocusable = true;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget()); // 매개변수 : 포커싱하고자 하는 위젯
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
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

void UMainMenu::TearDown()
{
	this->RemoveFromParent();
	this->bIsFocusable = false;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	FInputModeGameOnly InputModeData;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetShowMouseCursor(true);
}