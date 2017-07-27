// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Reporter.generated.h"

//Reporter Log
DECLARE_LOG_CATEGORY_EXTERN(ReporterLog, Log, All);

UCLASS()
class NEWTONPROJECT_API AReporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Report(const FString& report);

};
