// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CircNode.h"
#include "Component.h"
#include "Resistor.h"
#include "VoltageSource.h"
#include "GameFramework/Actor.h"
#include "Circuit.generated.h"

UCLASS()
class NEWTONPROJECT_API ACircuit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACircuit();

	// Getters and Setters
	/*int32 GetComponentCounter();
	void SetComponentCounter(int32 componentCounter);
	int32 GetCircNodeCounter();
	void SetCircNodeCounter(int32 circNodeCounter);
	TArray<AComponent*> GetComponentArray();
	void SetComponentArray(TArray<AComponent*> componentArray);
	TArray<ACircNode*> GetCircNodeArray();
	void SetCircNodeArray(TArray<ACircNode*> circNodeArray);*/
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create circuit
	virtual void AddComponent(AComponent *component);
	
	// Simulation commands
	virtual void Start();

private:
	int32 m_componentCounter;
	int32 m_circNodeCounter;
	TArray<AComponent*> m_componentArray;
	TArray<ACircNode*> m_circNodeArray;
	
};
