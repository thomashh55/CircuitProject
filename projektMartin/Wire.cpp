// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Wire.h"


// Sets default values
AWire::AWire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Getters and Setters
double AWire::GetCurrent()
{
	return m_current;
}

void AWire::SetCurrent(double current)
{
	m_current = current;
}

// Called when the game starts or when spawned
void AWire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AWire::GetPrefix()
{
	return "V";
}

