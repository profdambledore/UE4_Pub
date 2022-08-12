// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"

#include "StructEnumLibrary.generated.h"

UCLASS()
class UE4_PUB_API UStructEnumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FContainerItem
{
	GENERATED_USTRUCT_BODY();

public:


};

USTRUCT(BlueprintType)
struct FFurnishingMenuData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:


};

USTRUCT(BlueprintType)
struct FFurnishingWorldData
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <class AFurnishingParent> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator Rotation;
};