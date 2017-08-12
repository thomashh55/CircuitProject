// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"

#include "Component.h"


// Sets default values
AComponent::AComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

// Gets nodes of this component
TArray<ACircNode*> AComponent::GetCircNodeArray()
{
	return m_circNodeArray;
}

// Getter and setter for component identifier
void AComponent::SetId(int32 id)
{
	m_id = GetPrefix() + FString::FromInt(id);
}

FString AComponent::GetId()
{
	return m_id;
}

FString AComponent::GetPrefix()
{
	check(0 && "You must override this");
	return FString();
}

FString AComponent::GetCircLine()
{
	check(0 && "You must override this");
	return FString();
}

