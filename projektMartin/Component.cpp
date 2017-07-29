// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Component.h"


// Sets default values
AComponent::AComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Setters and Getters
FString AComponent::GetId()
{
	return m_id;
}

void AComponent::SetId(FString id)
{
	m_id = id;
}

double AComponent::GetCurrent()
{
	return m_current;
}

void AComponent::SetCurrent(double current)
{
	m_current = current;
}

ACircNode *AComponent::GetNode1()
{
	return m_node1;
}

void AComponent::SetNode1(ACircNode *node1)
{
	m_node1 = node1;
}

ACircNode *AComponent::GetNode2()
{
	return m_node2;
}

void AComponent::SetNode2(ACircNode *node2)
{
	m_node2 = node2;
}

// Called when the game starts or when spawned
void AComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}