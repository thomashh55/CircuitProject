// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CircNode.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Component.generated.h"

UCLASS(abstract)
class NEWTONPLUGIN_API AComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Gets nodes of this component
	TArray<ACircNode*> GetCircNodeArray();

	// Getter and setter for component identifier
	void SetId(int32 id);
	FString GetId();
	virtual FString GetPrefix();

	// Returns line for NgSpice
	virtual FString GetCircLine();

protected:
	FString m_id;
	TArray<ACircNode*> m_circNodeArray;
	
};
