// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "FurnishingParent.h"
#include "WorldManager.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	// Set Gravity scale to 0 on this character
	GetCharacterMovement()->GravityScale = 0;

	// Setup Camera and Sprint Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->TargetArmLength = MinZoomValue + ((MaxZoomValue - MinZoomValue) / 2);
	SpringArm->bDoCollisionTest = false;

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
		// Set the pointer to the world manager
		WM = Cast<AWorldManager>(FoundActors[0]);
		WM->PlayerRef = this;
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
		// Find distance between mouse world pos and closest floor or placeable object
		bool PlacementTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, MouseWorldLocation, MouseWorldLocation + (MouseWorldDirection * PlacementDistance), TraceChannel, FCollisionQueryParams(FName("DistTrace"), true));
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

	PlayerInputComponent->BindAction("CancelSelection", IE_Released, this, &APlayerCharacter::DeselectFurnishing);
	PlayerInputComponent->BindAction("PlaceFurnishing", IE_Released, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::SelectFurnishing(FFurnishingMenuData NewSelectedItem)
{
	if (FurnishingPlacer->GetStaticMesh() == nullptr || FurnishingPlacer->GetStaticMesh() != NewSelectedItem.Mesh)
	{
		bFurnishingSelected = true; FurnishingToPlace = NewSelectedItem;
		FurnishingPlacer->SetStaticMesh(NewSelectedItem.Mesh);
		// Set the new static meshes actual material to the CanPlaceFurnishing Material from the MaterialInterface
		CanPlaceMaterial = FurnishingToPlace.Mesh->GetMaterial(0)->GetMaterial();
	}
	else
	{
		DeselectFurnishing();
	}
}


void APlayerCharacter::DeselectFurnishing()
{
	bFurnishingSelected = false; FurnishingToPlace = {};
	FurnishingPlacer->SetStaticMesh(nullptr);
	CanPlaceMaterial = nullptr;
}

void APlayerCharacter::Interact()
{
	if (FurnishingPlacer->GetStaticMesh() != nullptr && HoveringButton == false)
	{
		if (WM->CanAffordPurchase(FurnishingToPlace.Price) == true)
		{
			WM->AddFurnishingToWorld(FurnishingToPlace, TraceHit.Location);
		}
	}
	else if (FurnishingPlacer->GetStaticMesh() == nullptr && HoveringButton == false)
	{
		// Get Mouse Location in world space
		PC->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
		// Find distance between mouse world pos and closest floor or placeable object
		bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, MouseWorldLocation, MouseWorldLocation + (MouseWorldDirection * PlacementDistance), ECC_GameTraceChannel2, FCollisionQueryParams(FName("DistTrace"), true));
		DrawDebugLine(GetWorld(), MouseWorldLocation, MouseWorldLocation + (MouseWorldDirection * 2000), FColor::Green, false, 1.f, ECC_GameTraceChannel2, 0.5f);

		if (TraceHit.GetActor()->GetClass()->IsChildOf<AFurnishingParent>() == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit"));
			SwapUIIndex(1);
		}
	}
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

