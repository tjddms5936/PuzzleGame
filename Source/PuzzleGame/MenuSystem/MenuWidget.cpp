// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"


void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface_)
{
	this->MenuInterface = MenuInterface_;
}

void UMenuWidget::Setup()
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

void UMenuWidget::TearDown()
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
