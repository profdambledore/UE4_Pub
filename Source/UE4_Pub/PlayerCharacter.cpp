// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "WorldManager.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	// Setup Camera and Sprint Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->TargetArmLength = MinZoomValue + ((MaxZoomValue - MinZoomValue) / 2);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	FurnishingPlacer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Furnishing Placement Tool"));
	FurnishingPlacer->SetVisibility(true);

	static ConstructorHelpers::FObjectFinder<UMaterial>CannotObject(TEXT("/Game/World/M_CannotPlace.M_CannotPlace"));
	if (CannotObject.Succeeded())
	{
		CannotPlaceMaterial = CannotObject.Object;
	}

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Complete the reference to the player controller
	PC = Cast<APlayerController>(GetController());	
	PC->bShowMouseCursor = true;

	// Get reference to the WorldManager
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldManager::StaticClass(), FoundActors);
	if (FoundActors.Num() == 0)
	{
		// If an interior cannot be found, give a warning
		UE_LOG(LogTemp, Warning, TEXT("Manager not found"));
	}
	else
	{
		// Set the pointer to the ship interior
		WM = Cast<AWorldManager>(FoundActors[0]);
	}
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFurnishingSelected == true)
	{
		// Get Mouse Location in world space
		PC->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
		// Find distance between mouse world pos and closest floor or placeable object  (TO:DO - Remove ability to trace to the placer helper object itself, this will stop it rising)
		bool PlacementTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, MouseWorldLocation, MouseWorldLocation + (MouseWorldDirection * 2000), TraceChannel, FCollisionQueryParams(FName("DistTrace"), true));
		//DrawDebugLine(GetWorld(), MouseWorldLocation, MouseWorldLocation + (MouseWorldDirection * 2000), FColor::Green, false, 1.f, ECC_WorldStatic, 0.5f);

		// Place the furnishing placer object where it is in the world space based on the mouse the distance away (rewrite comment)
		FurnishingPlacer->SetWorldLocation(TraceHit.Location);
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Axis Binds
	PlayerInputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveY);
	PlayerInputComponent->BindAxis("RotateX", this, &APlayerCharacter::RotateX);
	PlayerInputComponent->BindAxis("Zoom", this, &APlayerCharacter::Zoom);
}

void APlayerCharacter::SelectFurnishing(UStaticMesh* NewSelectedItem)
{
	bFurnishingSelected = true; FurnishingToPlace = NewSelectedItem;
	FurnishingPlacer->SetStaticMesh(NewSelectedItem);
	// Set the new static meshes actual material to the CanPlaceFurnishing Material from the MaterialInterface
	CanPlaceMaterial = FurnishingToPlace->GetMaterial(0)->GetMaterial();
}

void APlayerCharacter::DeselectFurnishing()
{
	bFurnishingSelected = false; FurnishingToPlace = nullptr;
	FurnishingPlacer->SetStaticMesh(nullptr);
	CanPlaceMaterial = nullptr;
}

bool APlayerCharacter::HasResourcesForFurnishing(float AmountRequired)
{
	return false;
}

void APlayerCharacter::MoveX(float AxisValue)
{
	if (AxisValue != 0)
	{
		AddActorLocalOffset(FVector((MovementStep * AxisValue), 0.0f, 0.0f), false, false);
	}
}

void APlayerCharacter::MoveY(float AxisValue)
{
	if (AxisValue != 0)
	{
		AddActorLocalOffset(FVector(0.0f, (MovementStep * AxisValue), 0.0f), false, false);
	}
}

void APlayerCharacter::RotateX(float AxisValue)
{
	if (AxisValue != 0)
	{
		AddActorWorldRotation(FRotator(0.0f, (RotationDegree * AxisValue), 0.0f), false, false);
	}
}

void APlayerCharacter::Zoom(float AxisValue)
{
	if (AxisValue != 0)
	{
		if (AxisValue == 1)
		{
			if (SpringArm->TargetArmLength + ZoomMultiplier >= MaxZoomValue)
			{
				SpringArm->TargetArmLength = MaxZoomValue;
			}
			else
			{
				SpringArm->TargetArmLength = SpringArm->TargetArmLength + ZoomMultiplier;
			}
		}
		else if (AxisValue == -1)
		{
			if (SpringArm->TargetArmLength - ZoomMultiplier <= MinZoomValue)
			{
				SpringArm->TargetArmLength = MinZoomValue;
			}
			else
			{
				SpringArm->TargetArmLength = SpringArm->TargetArmLength - ZoomMultiplier;
			}
		}
	}
}

