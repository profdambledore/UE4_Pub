// Fill out your copyright notice in the Description page of Project Settings.


#include "ContainerComponent.h"

// Sets default values for this component's properties
UContainerComponent::UContainerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UContainerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UContainerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UContainerComponent::AddToInventory(FContainerItem ItemToAdd, int Amount)
{
	if (CheckInInventory(ItemToAdd, Amount) == false)
	{
		// Add
		ModifyStruct.Item = ItemToAdd;
		ModifyStruct.Amount = Amount;

		ContainerInventory.Add(ModifyStruct);
	}
	else
	{
		// Find Index
		int j = FindIndexOfItem(ItemToAdd);
		ContainerInventory[j].Amount = ContainerInventory[j].Amount + Amount;
	}
}

bool UContainerComponent::RemoveFromInventory(FContainerItem ItemToRemove, int Amount)
{
	if (CheckInInventory(ItemToRemove, Amount) == true)
	{
		// Find Index
		int j = FindIndexOfItem(ItemToRemove);
		ContainerInventory[j].Amount = ContainerInventory[j].Amount - Amount;
		return true;
	}
	return false;

}

bool UContainerComponent::CheckInInventory(FContainerItem ItemToFind, int Amount)
{
	if (ContainerInventory.Num() != 0)
	{
		for (int i = 0; i <= ContainerInventory.Num(); i++)
		{
			if (ContainerInventory[i].Item.Name == ItemToFind.Name && ContainerInventory[i].Amount >= Amount)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

int UContainerComponent::FindIndexOfItem(FContainerItem ItemToFind)
{
	if (ContainerInventory.Num() != 0)
	{
		for (int i = 0; i <= ContainerInventory.Num(); i++)
		{
			if (ContainerInventory[i].Item.Name == ItemToFind.Name)
			{
				return i;
			}
		}
	}
	return -0;
}

