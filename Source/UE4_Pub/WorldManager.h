// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "StructEnumLibrary.h"

#include "WorldManager.generated.h"

UCLASS()
class UE4_PUB_API AWorldManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Add a new placed furnishing to the world
	UFUNCTION(BlueprintCallable)
		void AddFurnishingToWorld(FFurnishingMenuData NewFurnishing, FVector NewLocation);

	UFUNCTION(BlueprintCallable)
		bool CanAffordPurchase(float AmountRequired);

	UFUNCTION(BlueprintCallable)
		void BuyItem(float Amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
		TArray<FFurnishingWorldData> FurnishingsInWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
		FFurnishingWorldData AddFurnishing;

	// How much money the player currently has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Managers")
		float CurrentMoney = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Managers")
		float SellPercent = .8;

	class APlayerCharacter* PlayerRef;
};
