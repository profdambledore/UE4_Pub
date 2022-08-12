// Fill out your copyright notice in the Description page of Project Settings.

#include "FurnishingParent.h"
#include "PlayerCharacter.h"
#include "WorldManager.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldManager::AddFurnishingToWorld(FFurnishingMenuData NewFurnishing, FVector NewLocation)
{
	// First spawn in the new furnishing
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	GetWorld()->SpawnActor<class AFurnishingParent>(NewFurnishing.Class, NewLocation, FRotator(), ActorSpawnParams);

	// Next, set all properties in the defined struct
	AddFurnishing.Name = NewFurnishing.Name;
	AddFurnishing.Mesh = NewFurnishing.Mesh;
	AddFurnishing.Class = NewFurnishing.Class;
	AddFurnishing.Location = NewLocation;
	AddFurnishing.Rotation = FRotator();
	AddFurnishing.SellAmount = NewFurnishing.Price * SellPercent;

	// Then add it to the world array
	FurnishingsInWorld.Add(AddFurnishing);
	BuyItem(NewFurnishing.Price);

	// Deselect the item from the player if they have run out of money
	if (CanAffordPurchase(NewFurnishing.Price) == false)
	{
		PlayerRef->DeselectFurnishing();
	}
}

bool AWorldManager::CanAffordPurchase(float AmountRequired)
{
	if (CurrentMoney - AmountRequired <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void AWorldManager::BuyItem(float Amount)
{
	CurrentMoney = CurrentMoney - Amount;
}

