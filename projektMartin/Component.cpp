// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Component.h"


// Sets default values
AComponent::AComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Getters and Setters
/*double AComponent::GetCurrent()
{
	return m_current;
}

void AComponent::SetCurrent(double current)
{
	m_current = current;
}*/

TArray<ACircNode*> AComponent::GetCircNodeArray()
{
	return m_circNodeArray;
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

void AComponent::SetId(int32 id)
{
	m_id = GetPrefix() + FString::FromInt(id);
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
