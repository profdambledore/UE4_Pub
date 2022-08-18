// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FurnishingParent.h"

#include "Components/TextRenderComponent.h"

#include "Table.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PUB_API ATable : public AFurnishingParent
{
	GENERATED_BODY()
	

public:
	ATable();

	UFUNCTION(BlueprintCallable)
		void SetTableOwner(class APawn* CustomerOwner);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* TableNumberRender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TableNumber = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APawn* TableOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bOwned;


};
