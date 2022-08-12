// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "StructEnumLibrary.h"

#include "FurnishingParent.generated.h"

UCLASS()
class UE4_PUB_API AFurnishingParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFurnishingParent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetFurnishing(FFurnishingWorldData NewData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Furnishing Data")
		FFurnishingWorldData Data;

};
