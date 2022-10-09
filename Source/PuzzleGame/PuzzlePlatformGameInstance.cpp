// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem./MainMenu.h"
#include "MenuSystem/MenuWidget.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

const static FName SESSION_NAME = FName("GameSession");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");

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
	UE_LOG(LogTemp, Warning, TEXT("222222222222222222222222222Found Class Class Found Class %s!!!!!!!!!!!!!!"), *MenuClass->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *CancelMenuClass->GetName());


	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();


	if (OnlineSubsystem != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Found OnlineSubsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			UE_LOG(LogTemp, Warning, TEXT("Found SessionInterface"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnJoinSessionComplete);
		}
	}
	else {
		// UE_LOG(LogTemp, Warning, TEXT("Found Failed OnlineSubsystem"));
	}
	if (GEngine) {
		GEngine->OnNetworkFailure().AddUObject(this, &UPuzzlePlatformGameInstance::OnNetworkFailure);
	}
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	MainMenu = CreateWidget<UMainMenu>(this, MenuClass, FName(MenuClass->GetName()));

	MainMenu->Setup();

	MainMenu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::HostServer(FString ServerName)
{
	DesiredServerName = ServerName;

	if (SessionInterface.IsValid()) {
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr) {
			// 이미 존재하는 Session이 있다면
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else {
			// 존재하는 Session이 없다면
			CreateSession();
		}
	}
}

void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success) return;

	For_CallBackBool = true;
	// GetEngine() : GameInstance만의 메서드. 
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Green, TEXT("Hosting"));
	
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/Maps/Lobby?listen");
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
	if (!Success && !SessionSearchPtr.IsValid() && MainMenu == nullptr) return;

	TArray<FServerData> ServerDataes;

	for (FOnlineSessionSearchResult& Result : SessionSearchPtr->SearchResults) {
		UE_LOG(LogTemp, Warning, TEXT("Found Session Name : %s"), *Result.GetSessionIdStr());
		FServerData Data;
		Data.ServerName = Result.GetSessionIdStr();
		Data.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections; // CreateSession()에서 설정 한 MaxPlayer 수
		Data.CurrenctPlayers = Data.MaxPlayers - Result.Session.NumOpenPublicConnections; // 현재 연결되어있는 플레이어 수
		Data.HostUserName = Result.Session.OwningUserName;
		FString StringData;
		if (Result.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, StringData)) {
			Data.ServerName = StringData;
		}
		else {
			Data.ServerName = FString("Default Server Name");
		}
		ServerDataes.Add(Data);
	}
	MainMenu->SetServerList(ServerDataes);
	UE_LOG(LogTemp, Warning, TEXT("Find Session Complete!!"));
}

void UPuzzlePlatformGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;

	FString Address;

	if (!SessionInterface->GetResolvedConnectString(SessionName, Address)) {
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string"));
		return;
	}
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Black, FString::Printf(TEXT("Joining %s"), *Address));
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(*Address, ETravelType::TRAVEL_Absolute);
	
}

void UPuzzlePlatformGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	LoadMenu();
}


void UPuzzlePlatformGameInstance::CreateSession()
{
	if (SessionInterface.IsValid()) {
		FOnlineSessionSettings SessionSetting;
		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL") {
			SessionSetting.bIsLANMatch = true; // 이 게임은 LAN 전용이며 외부 플레이어에게 표시되지 않습니다.
		}
		else {
			SessionSetting.bIsLANMatch = false;
		}
		// 아래 3개의 작업을 해주지 않으면 찾을 수 있는 세션은 0개가 될 것이다. (bIsLANMatch, NumPublicConnections, bShouldAdvertise)
		SessionSetting.NumPublicConnections = 5; // 공지된 공개적으로 사용 가능한 연결 수  // NumPrivateConnections : 비공개(초대/비밀번호) 전용 연결 수
		SessionSetting.bShouldAdvertise = true; // 온라인에서 세션을 볼 수 있도록 하는데, 이는 친구들에게 맞춤 초대장을 보내는 것을 광고를 통해 우회가능
		// 세션 찾기를 호출 할 때의 쿼리 매개변수를 살펴보자 -> Go to Init() 에서 SessionSearch부분 보기
		SessionSetting.bUsesPresence = true; // Lobby로 조인하기 위한 조건
		SessionSetting.bUseLobbiesIfAvailable = true; // Lobby로 CreateSession을 하기 위한 조건
		SessionSetting.Set(SERVER_NAME_SETTINGS_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSetting);
	}
}

void UPuzzlePlatformGameInstance::StartSession()
{
	if (SessionInterface != nullptr) {
		SessionInterface->StartSession(SESSION_NAME);
	}
}

void UPuzzlePlatformGameInstance::ServerListRefresh()
{
	// ※ new 키워드는 힙에 무언가를 만든다.
	SessionSearchPtr = MakeShareable(new FOnlineSessionSearch()); // TSharedPtr 을 얻고
	if (SessionSearchPtr.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Find Session Start"));

		SessionSearchPtr->bIsLanQuery = false; // 쿼리가 LAN 일치를 위한 것인지 여부.
	   /*
		false로 해도 문제는 없음 why?  쿼리 설정만 제거하는건
	   // Lan일치와 Non-Lan 일치를 모두 찾을 것이기 때문이다.
	   */

	   /*
	   SessionSearchPtr->QuerySettings.Set(~~)// Steam 얻을 때 사용할 것임.
	   아이디어는 QuerySettings가 FOnlineSessionSearch의 API에 의해 정의되는 것이 아니라, 사용 중인 API에 의해 정의된다는 것이다.
	   */

	   // TSharedRef로 변환해주고 매개변수에 넣어야함
	
		// Set함수 : SEARCH_PRESENCE(key)를 true(value)로 설정.
		SessionSearchPtr->MaxSearchResults = 100; // Defaults값이 없어서 설정하지 않으면 자신의 게임은 찾을 수가 없음
		SessionSearchPtr->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		bool testing = false;
		if (SessionSearchPtr->QuerySettings.Get(SEARCH_PRESENCE, testing) && testing) {
			UE_LOG(LogTemp, Warning, TEXT("testing changes to true"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("testing  not changes to true. still false"));
		}

		SessionInterface->FindSessions(0, SessionSearchPtr.ToSharedRef());
	}
}

void UPuzzlePlatformGameInstance::Join(int index)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearchPtr.IsValid()) return;

	if (MainMenu != nullptr) {
		MainMenu->TearDown();
	}
	
	For_CallBackBool = true;

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearchPtr->SearchResults[index]);
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

bool UPuzzlePlatformGameInstance::CallBackBool(bool input)
{
	if (For_CallBackBool) {
		input = For_CallBackBool;
	}
	For_CallBackBool = false;
	return input;
}



