// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "StructEnumLibrary.h"

#include "ContainerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_PUB_API UContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UContainerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void AddToInventory(FContainerItem ItemToAdd, int Amount);

	UFUNCTION(BlueprintCallable)
		bool RemoveFromInventory(FContainerItem ItemToRemove, int Amount);

	UFUNCTION(BlueprintCallable)
		bool CheckInInventory(FContainerItem ItemToFind, int Amount);

	UFUNCTION(BlueprintCallable)
		int FindIndexOfItem(FContainerItem ItemToFind);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FContainerSlot> ContainerInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FContainerSlot ModifyStruct;
		
};
