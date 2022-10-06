// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "MainMenu.h"

#include "Components/Button.h"



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
