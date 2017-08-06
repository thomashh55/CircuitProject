// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CircNode.generated.h"

UCLASS()
class MYPROJECT2_API ACircNode : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACircNode();

	// Getters and Setters
	int32 GetId();
	void SetId(int32 id);
	double GetVoltage();
	void SetVoltage(double voltage);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int32 m_id;
	double m_voltage;

};