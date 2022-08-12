// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "StructEnumLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class UE4_PUB_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Furnishing Functions
	UFUNCTION(BlueprintCallable)
		void SelectFurnishing(FFurnishingMenuData NewSelectedItem);

	UFUNCTION(BlueprintCallable)
		void DeselectFurnishing();

	UFUNCTION(BlueprintCallable)
		void CreateFurnishing();

	UFUNCTION(BlueprintCallable)
		bool HasResourcesForFurnishing(float AmountRequired);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector	MouseWorldLocation;
	FVector MouseWorldDirection;

	// Inputs
	// Axis
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void RotateX(float AxisValue);
	void Zoom(float AxisValue);

public:	
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* DefaultSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* FurnishingPlacer;

	// References
	APlayerController* PC;
	class AWorldManager* WM;

	// Properties
	// How much the value of SpringArmLength changes per update
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Properties")
		float ZoomMultiplier = 10;

	// The minimum SpringArmLength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Properties")
		float MinZoomValue = 500;

	// The maximum SpringArmLength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Properties")
		float MaxZoomValue = 1000;

	// How much the camera's angle changes per update
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Properties")
		float RotationDegree = 2;

	// How many unreal units to move each step
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Properties")
		float MovementStep = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement Properties")
		bool bFurnishingSelected = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement Properties")
		float PlacementDistance = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement Properties")
		bool HoveringButton = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement Properties")
		FFurnishingMenuData FurnishingToPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement Properties")
		UMaterial* CanPlaceMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement Properties")
		UMaterial* CannotPlaceMaterial;

	// Placement Trace Properties
	// As we are tracing in tick, we define the trace properties here to reduce memory usage
	// Generate information for the trace
	FHitResult TraceHit = FHitResult(ForceInit);
	ECollisionChannel TraceChannel = ECC_GameTraceChannel2;

	//float DistanceToFloor;
};
