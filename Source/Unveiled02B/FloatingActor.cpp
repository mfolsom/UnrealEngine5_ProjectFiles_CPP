// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FloatingActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Define Static Mesh Component and attach to Root Component
	FloatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	FloatMesh->SetupAttachment(RootComponent);
	// construct a cube mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// if the cube mesh is found, set it as the mesh for the static mesh component and set its location
	if (CubeMesh.Succeeded())
	{
		FloatMesh->SetStaticMesh(CubeMesh.Object);
		FloatMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Define New Location and Rotation
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
    // Define Running Time and Delta Height
	float RunningTime = GetGameTimeSinceCreation();
	// Use Sin to create a floating effect
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	float DeltaRotation = DeltaTime * RotationSpeed;
	// Update location and rotation
	NewLocation.Z += DeltaHeight * FloatSpeed;
	NewRotation.Yaw += DeltaRotation;
	// Set new location and rotation
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

