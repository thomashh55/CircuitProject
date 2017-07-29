// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Component.h"
#include "GameFramework/Actor.h"
#include "Wire.generated.h"

UCLASS()
class NEWTONPROJECT_API AWire : public AComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
