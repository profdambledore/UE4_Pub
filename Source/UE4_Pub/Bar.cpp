// Fill out your copyright notice in the Description page of Project Settings.


#include "Bar.h"

// Sets default values
ABar::ABar() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup the components
	CaravanMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Caravan Mesh"));
	CaravanMesh->SetCollisionProfileName("Furnishing");

	BarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bar Mesh"));
	BarMesh->SetRelativeLocation(FVector(-80.0f,0.0f,50.0f));
	BarMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	BarMesh->SetCollisionProfileName("Furnishing");

	Inventory = CreateDefaultSubobject<UContainerComponent>(TEXT("Inventory"));

	// Find and set the two meshes
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CaravanObject(TEXT("/Game/PolygonShops/Meshes/Vehicles/SM_Veh_Food_Trailer_02_Preset.SM_Veh_Food_Trailer_02_Preset"));
	if (CaravanObject.Succeeded())
	{
		CaravanMesh->SetStaticMesh(CaravanObject.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>BarObject(TEXT("/Game/PolygonShops/Meshes/Props/SM_Prop_Bar_Bench_01.SM_Prop_Bar_Bench_01"));
	if (BarObject.Succeeded())
	{
		BarMesh->SetStaticMesh(BarObject.Object);
	}

}

// Called when the game starts or when spawned
void ABar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

