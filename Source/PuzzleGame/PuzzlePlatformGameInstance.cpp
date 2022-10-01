// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem./MainMenu.h"
#include "MenuSystem/MenuWidget.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

const static FName SESSION_NAME = TEXT("My session game");

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


	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();


	if (OnlineSubsystem != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Found OnlineSubsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			UE_LOG(LogTemp, Warning, TEXT("Found SessionInterface"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionComplete);

			// �� new Ű����� ���� ���𰡸� �����.
			SessionSearchPtr = MakeShareable(new FOnlineSessionSearch()); // TSharedPtr �� ���
			if (SessionSearchPtr.IsValid()) {
				UE_LOG(LogTemp, Warning, TEXT("Find Session Start"));

				 SessionSearchPtr->bIsLanQuery = true; // ������ LAN ��ġ�� ���� ������ ����.
				/*
				 false�� �ص� ������ ���� why?  ���� ������ �����ϴ°� 
				// Lan��ġ�� Non-Lan ��ġ�� ��� ã�� ���̱� �����̴�.
				*/

				/*
				SessionSearchPtr->QuerySettings.Set(~~)// Steam ���� �� ����� ����. 
				���̵��� QuerySettings�� FOnlineSessionSearch�� API�� ���� ���ǵǴ� ���� �ƴ϶�, ��� ���� API�� ���� ���ǵȴٴ� ���̴�.
				*/

				// TSharedRef�� ��ȯ���ְ� �Ű������� �־����
				SessionInterface->FindSessions(0, SessionSearchPtr.ToSharedRef());
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found Failed OnlineSubsystem"));
	}
	
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
	if (SessionInterface.IsValid()) {
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr) {
			// �̹� �����ϴ� Session�� �ִٸ�
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else {
			// �����ϴ� Session�� ���ٸ�
			CreateSession();
		}
	}
}

void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success) return;

	For_CallBackBool = true;
	// GetEngine() : GameInstance���� �޼���. 
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Green, TEXT("Hosting"));
	
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success) {
		CreateSession();
		UE_LOG(LogTemp, Warning, TEXT("Exsisted Session Destroy and New Session Create!!!"));
	}
}

void UPuzzlePlatformGameInstance::OnFindSessionComplete(bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("Find Session Complete!!"));
	if (!Success && !SessionSearchPtr.IsValid()) return;

	for (FOnlineSessionSearchResult& Result : SessionSearchPtr->SearchResults) {
		UE_LOG(LogTemp, Warning, TEXT("Found Session Name : %s"), *Result.GetSessionIdStr());
	}
}

void UPuzzlePlatformGameInstance::CreateSession()
{
	if (SessionInterface.IsValid()) {
		FOnlineSessionSettings SessionSetting;

		// �Ʒ� 3���� �۾��� ������ ������ ã�� �� �ִ� ������ 0���� �� ���̴�.
		SessionSetting.bIsLANMatch = true; // �� ������ LAN �����̸� �ܺ� �÷��̾�� ǥ�õ��� �ʽ��ϴ�.
		SessionSetting.NumPublicConnections = 2; // ������ ���������� ��� ������ ���� ��  // NumPrivateConnections : �����(�ʴ�/��й�ȣ) ���� ���� ��
		SessionSetting.bShouldAdvertise = true; // �¶��ο��� ������ �� �� �ֵ��� �ϴµ�, �̴� ģ���鿡�� ���� �ʴ����� ������ ���� ���� ���� ��ȸ����
		// ���� ã�⸦ ȣ�� �� ���� ���� �Ű������� ���캸�� -> Go to Init() ���� SessionSearch�κ� ����

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSetting);
	}
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Black, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(*Address, ETravelType::TRAVEL_Absolute);
	
	For_CallBackBool = true;
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

	// ���� ���� �� �ܼ�â�� quit�ϸ� ������ ������. �װ� C++�� ����
	Controller->ConsoleCommand(FString("quit"));
}

bool UPuzzlePlatformGameInstance::CallBackBool(bool input)
{
	if (For_CallBackBool) {
		input = For_CallBackBool;
	}
	For_CallBackBool = false;
	return input;
}



