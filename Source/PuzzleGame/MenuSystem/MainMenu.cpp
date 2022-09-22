// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"

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
	if (MenuInterface != nullptr) {
		//메모리 사용에 주의하고 싶을 땐 const로 선언
		if (!ensure(IPAdressField != nullptr)) return;
		const FString& IPAdress = IPAdressField->GetText().ToString();
		MenuInterface->Join(IPAdress); // 순수가상함수 호출! 해당 함수는 어디서 구현되어 있을까?
		TearDown();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("MenuInterface == nullptr"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Join Server!!!"));
	return;
}

void UMainMenu::JoinMenuCancel()
{
	if (ensure(MenuSwitcher == nullptr)) return;
	if (ensure(MainMenu == nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}


