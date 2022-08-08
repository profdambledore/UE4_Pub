// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "ContainerComponent.h"

#include "StructEnumLibrary.h"

#include "Bar.generated.h"

UCLASS()
class UE4_PUB_API ABar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* CaravanMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BarMesh;

};
