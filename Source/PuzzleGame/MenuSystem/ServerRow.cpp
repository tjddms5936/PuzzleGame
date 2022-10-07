// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "MainMenu.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UServerRow::Initialize() {
	bool Success = Super::Initialize(); // 혹시 Initialize가 false를 반환 할 수 있으므로
	if (!Success) return false;


	ServerName->Font.Size = TextSize;
	HostName->Font.Size = TextSize;
	PlayerNum->Font.Size = TextSize;

	return true;
}

void UServerRow::Setup(UMainMenu* InParent, uint32 Inindex)
{
	Parent = InParent;
	index = Inindex;


	// ToDo : SetUp
	if (!ensure(ServerBtn != nullptr)) return;
	ServerBtn->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
	Parent->SelectIndex(index);
}
