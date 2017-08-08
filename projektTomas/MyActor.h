// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Circuit.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ngspice/sharedspice.h"
#include "ngspice/dvec.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sstream>
#include "MyActor.generated.h"

UCLASS()
class MYPROJECT2_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();
	ACircuit *circuit;
	ACircuit *circuit2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
