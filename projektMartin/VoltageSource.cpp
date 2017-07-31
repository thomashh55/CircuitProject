// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "VoltageSource.h"


// Sets default values
AVoltageSource::AVoltageSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Getters and Setters
double AVoltageSource::GetDirectCurrent()
{
	return m_directCurrent;
}

void AVoltageSource::SetDirectCurrent(double directCurrent)
{
	m_directCurrent = directCurrent;
}

// Called when the game starts or when spawned
void AVoltageSource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVoltageSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AVoltageSource::GetPrefix()
{
	return "V";
}

