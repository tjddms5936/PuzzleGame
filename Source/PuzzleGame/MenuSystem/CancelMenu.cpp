// Fill out your copyright notice in the Description page of Project Settings.


#include "CancelMenu.h"
#include "Components/Button.h"


bool UCancelMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	// ToDo Setup
	if (!ensure(CancelBtn != nullptr)) return false;
	CancelBtn->OnClicked.AddDynamic(this, &UCancelMenu::CancelMenuFunc);

	if (!ensure(QuitBtn != nullptr)) return false;
	QuitBtn->OnClicked.AddDynamic(this, &UCancelMenu::QuitMenuFunc);
		
	return true;
}

void UCancelMenu::CancelMenuFunc()
{
	if (MenuInterface != nullptr) {
		MenuInterface->CancelMenu();
		TearDown();
		
	}
}

void UCancelMenu::QuitMenuFunc()
{
	if (MenuInterface != nullptr) {
		MenuInterface->QuitMenu();
		TearDown();
	}
}
