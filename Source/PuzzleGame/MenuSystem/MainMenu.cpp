// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowWBPClass(TEXT("/Game/MenuSystem/WPB_ServerRow"));
	if (!ensure(ServerRowWBPClass.Class != nullptr)) return;
	ServerRowClass = ServerRowWBPClass.Class;


}


void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
	// JoinServer �Լ����� �ϴ� �۾� �ű��
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	if (ServerScrollBox != nullptr) {
		ServerScrollBox->ClearChildren();
	}
	
	uint32 index = 0;
	for (const FString& ServerName : ServerNames) {
		if (!ensure(ServerRowClass != nullptr)) return;
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);
		ServerRow->ServerName->SetText(FText::FromString(ServerName));
		
		ServerRow->Setup(this, index);
		++index;

		if (!ensure(ServerScrollBox != nullptr)) return;
		ServerScrollBox->AddChild(ServerRow);
	}

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
	if (MenuInterface != nullptr) {
		MenuInterface->ServerListRefresh();
	}
}

void UMainMenu::JoinServer()
{
	if (SelectedIndex.IsSet() && MenuInterface != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Selected Index %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Selected Index isn't setted"));
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


void UMainMenu::SelectIndex(uint32 index)
{
	// SelectedIndex�� �Ҵ��ϱ� ���� TOptional�� ������ �� �ʿ�� ����.
	// TOptional���� ��ȣ �Ҵ� �����ڿ� ���� �����ε尡 �ֱ� �����̴�.
	SelectedIndex = index;

	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	for (int i = 0; i < ServerScrollBox->GetChildrenCount(); i++) {
		UServerRow* Row = Cast<UServerRow>(ServerScrollBox->GetChildAt(i));
		if (Row) {
			// �ܶ� ������ ��� : ������ false��� �ڿ��� ������� false ��ȯ. true��� �ڿ��Ϳ� ���� ��ȯ
			Row->IsSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}

