// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnishingParent.h"

// Sets default values
AFurnishingParent::AFurnishingParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Furnishing Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AFurnishingParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFurnishingParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFurnishingParent::SetFurnishing(FFurnishingWorldData NewData)
{
	// Set the property
	Data = NewData;

	// Then set the mesh
	Mesh->SetStaticMesh(NewData.Mesh);
}

