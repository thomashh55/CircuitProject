// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CircNode.generated.h"

UCLASS()
class NEWTONPLUGIN_API ACircNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACircNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Getter and setter for component identifier
	int32 GetId();
	void SetId(int32 id);

	// Getters and setters for measurements
	double GetVoltage(int index);
	void AddVoltage(double voltage);
	void ResetVoltageArray();

private:
	int32 m_id;
	TArray<double> m_voltageArray;
	
};
