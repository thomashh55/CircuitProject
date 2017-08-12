// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CircNode.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wire.generated.h"

UCLASS()
class NEWTONPLUGIN_API AWire : public AActor
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

	// Assigns nodes to the wire
	virtual void AddCircNodes(ACircNode *circNode1, ACircNode *circNode2);

	// Gets nodes of this component
	TArray<ACircNode*> GetCircNodeArray();

	// Getter and setter for component identifier
	void SetId(int32 id);
	FString GetId();
	virtual FString GetPrefix();

	// Returns line for NgSpice
	virtual FString GetCircLine();

	// Getters and setters for measurements
	double GetCurrent(int index);
	void AddCurrent(double current);
	void ResetCurrentArray();

private:
	static const FString m_prefix;
	FString m_id;
	TArray<ACircNode*> m_circNodeArray;
	TArray<double> m_currentArray;
	
};
