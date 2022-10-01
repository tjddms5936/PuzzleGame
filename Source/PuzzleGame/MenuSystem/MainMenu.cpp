// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowWBPClass(TEXT("/Game/MenuSystem/WPB_ServerRow"));
	if (!ensure(ServerRowWBPClass.Class != nullptr)) return;
	ServerRowClass = ServerRowWBPClass.Class;


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
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Join Server!!!"));

		UWorld* World = this->GetWorld();

		if (!ensure(ServerRowClass != nullptr)) return;
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);

		if (!ensure(ServerScrollBox != nullptr)) return;
		ServerScrollBox->AddChild(ServerRow);

		if (MenuInterface->CallBackBool(false)) {
			// ���� Join�� ���������� �Ǹ� ��ȯ������ true�� �� ����.
			TearDown();
		}
		else {
			GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, FString::Printf(TEXT("MenuInterface->CallBackBool(false) return false!")));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("MenuInterface == nullptr"));
	}
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


