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
	FString GetId();
	void SetId(int32 id);
	/*double GetCurrent();
	void SetCurrent(double current);
	ACircNode *GetNode1();
	void SetNode1(ACircNode *node1);
	ACircNode *GetNode2();
	void SetNode2(ACircNode *node2);*/

//protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns prefix for NgSpice
	virtual FString GetPrefix();

private:
	FString m_id;
	double m_current;
	ACircNode *m_node1;
	ACircNode *m_node2;

};
