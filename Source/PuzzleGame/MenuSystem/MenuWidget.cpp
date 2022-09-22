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
	InputModeData.SetWidgetToFocus(this->TakeWidget()); // �Ű����� : ��Ŀ���ϰ��� �ϴ� ����
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetShowMouseCursor(true);

	/*
	���� ���ǿ��� ������ ���� ���� �޽����� ǥ�õǴ� ���:
	LogPlayerController: ����: InputMode:UIOnly - ��Ŀ���� ���� �� ���� ���� SObjectWidget [Widget.cpp(710)]�� ��Ŀ���� ���߷��� �մϴ�!
	���� �ڵ� ������ �߰��� ������.
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
