// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Pawn.h"
#include "Table.h"

ATable::ATable() : Super()
{
	// Add the table number render
	TableNumberRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Number Render"));
}

void ATable::SetTableOwner(APawn* CustomerOwner)
{
	bOwned = true;
	TableOwner = CustomerOwner;
}
