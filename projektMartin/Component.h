// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CircNode.h"
#include "GameFramework/Actor.h"
#include "Component.generated.h"

UCLASS(abstract)
class NEWTONPROJECT_API AComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComponent();

	// Getters and Setters
	/*double GetCurrent();
	void SetCurrent(double current);*/
	TArray<ACircNode*> *GetNodeArray();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Getter and setter for component identifier
	void SetId(int32 id);
	virtual FString GetPrefix();

	// Returns line for NgSpice
	virtual FString GetCircLine();

protected:
	FString m_id;
	double m_current;
	TArray<ACircNode*> *m_nodeArray;
	
};
