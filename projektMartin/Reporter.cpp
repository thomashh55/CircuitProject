// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Reporter.h"

//Reporter Log
DEFINE_LOG_CATEGORY(ReporterLog);

// Sets default values
AReporter::AReporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AReporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReporter::Report(const FString& report)
{
	UE_LOG(ReporterLog, Warning, TEXT("Report: %s"), *report);
}
