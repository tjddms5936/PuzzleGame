// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	
}


bool UMainMenu::Initialize() {
	bool Success = Super::Initialize(); // Ȥ�� Initialize�� false�� ��ȯ �� �� �����Ƿ�
	if (!Success) return false; 

	// ToDo : SetUp
	if (!ensure(HostBtn != nullptr)) return false;
	HostBtn->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinBtn != nullptr)) return false;
	JoinBtn->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(JoinMenu_JoinBtn != nullptr)) return false;
	JoinMenu_JoinBtn->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(JoinMenu_CancelBtn != nullptr)) return false;
	JoinMenu_CancelBtn->OnClicked.AddDynamic(this, &UMainMenu::JoinMenuCancel);

	if (!ensure(ExitBtn != nullptr)) return false;
	ExitBtn->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr) {
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, FString::Printf(TEXT("MainMenu.cpp -> HostServer() -> Called Message")));
		MenuInterface->HostServer(); // ���������Լ� ȣ��! �ش� �Լ��� ��� �����Ǿ� ������?
		if (MenuInterface->CallBackBool(false)) {
			// ���� HostServer�Լ��� ���� CreateOnlineSession�� �Ǿ��ٸ� false���� true�� �ٲ�� ��ȯ�ȴ�. �ƴϸ� false �״�� ��ȯ.
			TearDown();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("MenuInterface == nullptr"));
	}
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
		//�޸� ��뿡 �����ϰ� ���� �� const�� ����
		//if (!ensure(IPAdressField != nullptr)) return;
		//const FString& IPAdress = IPAdressField->GetText().ToString();
		//MenuInterface->Join(IPAdress); // ���������Լ� ȣ��! �ش� �Լ��� ��� �����Ǿ� ������?
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
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::ExitGame()
{
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Black, FString::Printf(TEXT("Exit Game")));
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->ExitGameFunc();

}


