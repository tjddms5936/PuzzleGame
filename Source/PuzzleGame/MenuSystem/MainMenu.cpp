// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

#include "ServerRow.h"
#define LOCTEXT_NAMESPACE "MyNamespace"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowWBPClass(TEXT("/Game/MenuSystem/WPB_ServerRow"));
	if (!ensure(ServerRowWBPClass.Class != nullptr)) return;
	ServerRowClass = ServerRowWBPClass.Class;


}


void UMainMenu::SetServerList(TArray<FServerData> ServerNames)
{
	// JoinServer 함수에서 하던 작업 옮기기
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	if (ServerScrollBox != nullptr) {
		ServerScrollBox->ClearChildren();
	}
	
	uint32 index = 0;
	for (const FServerData& ServerData : ServerNames) {
		if (!ensure(ServerRowClass != nullptr)) return;
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);
		ServerRow->ServerName->SetText(FText::FromString(ServerData.ServerName));
		ServerRow->HostName->SetText(FText::FromString(ServerData.HostUserName));
		ServerRow->PlayerNum->SetText(FText::Format(LOCTEXT("Example", "{0}/{1}"), ServerData.CurrenctPlayers, ServerData.MaxPlayers));
		
		ServerRow->Setup(this, index);
		++index;

		if (!ensure(ServerScrollBox != nullptr)) return;
		ServerScrollBox->AddChild(ServerRow);
	}

}

bool UMainMenu::Initialize() {
	bool Success = Super::Initialize(); // 혹시 Initialize가 false를 반환 할 수 있으므로
	if (!Success) return false; 

	// ToDo : SetUp
	if (!ensure(HostBtn != nullptr)) return false;
	HostBtn->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);

	if (!ensure(HostMenu_HostBtn != nullptr)) return false;
	HostMenu_HostBtn->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(HostMenu_CancelBtn != nullptr)) return false;
	HostMenu_CancelBtn->OnClicked.AddDynamic(this, &UMainMenu::MenuCancel);

	if (!ensure(JoinBtn != nullptr)) return false;
	JoinBtn->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(JoinMenu_JoinBtn != nullptr)) return false;
	JoinMenu_JoinBtn->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(JoinMenu_CancelBtn != nullptr)) return false;
	JoinMenu_CancelBtn->OnClicked.AddDynamic(this, &UMainMenu::MenuCancel);

	if (!ensure(ExitBtn != nullptr)) return false;
	ExitBtn->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);

	return true;
}

void UMainMenu::OpenHostMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(HostMenu);
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr) {
		if (ServerNameInput == nullptr) return;

		FString ServerName = ServerNameInput->GetText().ToString();

		MenuInterface->HostServer(ServerName); // 순수가상함수 호출! 해당 함수는 어디서 구현되어 있을까?
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

void UMainMenu::MenuCancel()
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
	// SelectedIndex에 할당하기 위해 TOptional을 역참조 할 필요는 없다.
	// TOptional에는 등호 할당 연산자에 대한 오버로드가 있기 떄문이다.
	SelectedIndex = index;

	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	for (int i = 0; i < ServerScrollBox->GetChildrenCount(); i++) {
		UServerRow* Row = Cast<UServerRow>(ServerScrollBox->GetChildAt(i));
		if (Row) {
			// 단락 연산자 사용 : 왼쪽이 false라면 뒤에것 상관없이 false 반환. true라면 뒤에것에 따라서 반환
			Row->IsSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}

