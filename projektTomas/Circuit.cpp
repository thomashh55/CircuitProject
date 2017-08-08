
#include "Circuit.h"

//Circuit Log
//DEFINE_LOG_CATEGORY(CircuitLog);

// Sets default values
ACircuit::ACircuit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

ACircuit::~ACircuit()
{
	NgSpice::getInstance().RemoveCircuit(this);
}

// Getters and Setters
/*TArray<AComponent*> ACircuit::GetComponentArray()
{
return m_componentArray;
}

void ACircuit::SetComponentArray(TArray<AComponent*> componentArray)
{
m_componentArray = componentArray;
}
TArray<ACircNode*> ACircuit::GetCircNodeArray()
{
return m_circNodeArray;
}
void ACircuit::SetCircNodeArray(TArray<ACircNode*> circNodeArray)
{
m_circNodeArray = circNodeArray;
}*/

void ACircuit::SetindexToCircuitArray(int index) {
	indexToCircuitArray = index;
}

int ACircuit::GetindexToCircuitArray() {
	return indexToCircuitArray;
}

// Called when the game starts or when spawned
void ACircuit::BeginPlay()
{
	Super::BeginPlay();
	time = 0;

	// Adds this circuit to NgSpice
	indexToCircuitArray = NgSpice::getInstance().AddCircuit(this);
}

// Called before destroing the actor
void ACircuit::BeginDestroy()
{
	Super::BeginDestroy();

	// Removes this circuit from NgSpice
	NgSpice::getInstance().RemoveCircuit(this);
}

// Called every frame
bool ubehol = false;
void ACircuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	time += DeltaTime;

	if ((time > 10.0)&&(ubehol == false)) {
		UE_LOG(LogTemp, Warning, TEXT("UBEHLO 10 SEKUND\n"));
		ubehol = true;
	}
}

// 100MS je index o 1,, teda 0.1s je index o jedna, preto to treba zaokruhlit a potom vynasobit krat 10
float ACircuit::MeasureCurrent(AWire wire, float time) {

	return 0;
}

float ACircuit::MeasureCurrent(AWire wire) {
	return 0;
}

float ACircuit::MeasureVoltage(ACircNode node, float time) {
	return 0;
}

float ACircuit::MeasureVoltage(ACircNode node) {
	return 0;
}


// Adds component to the circuit
void ACircuit::AddComponent(AComponent *component)
{
	m_componentArray.Add(component);
	for (ACircNode *node : component->GetCircNodeArray()) {
		m_circNodeArray.Add(node);
	}
}

// Adds wires to the circuit
void ACircuit::AddWire(AWire *wire, ACircNode *circNode1, ACircNode *circNode2)
{
	m_componentArray.Add(wire);
	wire->AddCircNodes(circNode1, circNode2);
}

// Get array of components
TArray<AComponent*> ACircuit::GetComponentArray()
{
	return m_componentArray;
}

void ACircuit::FillResults() {
	for (int i = 0; i < NgSpice::vectorscount; i++) {
		double * vectorvalue = NgSpice::vectors[i]->v_realdata;

		if ( (NgSpice::vectors[i]->v_name)[0] == 'V' ) {
			for (ACircNode *circNode : m_circNodeArray) {
				if ( circNode->GetId() == (int) ( (NgSpice::vectors[i]->v_name)[2] - '0' ) ) {
					//UE_LOG(LogTemp, Warning, TEXT("prave sa naplnil node s menom: %s\n"), *(FString(vectors[i]->v_name)));
					circNode->SetVoltage(vectorvalue);
				}
			}
		}
		else {
			for (AComponent *component : m_componentArray) {
				if (component->GetCircLine()[1] == (TCHAR)(NgSpice::vectors[i]->v_name)[1]) {
					//UE_LOG(LogTemp, Warning, TEXT("prave sa naplnil voltage dummy s menom: %s\n"), *(FString(vectors[i]->v_name)));
					UE_LOG(LogTemp, Warning, TEXT("dlzka vektora je %d\n"), NgSpice::vectors[i]->v_length);
					((AVoltageSource*)component)->SetSimulatedCurrent(vectorvalue);
				}
			}
		}
	}
}

// Simulation commands
void ACircuit::Start()
{
	int32 m_componentCounter = 0;
	int32 m_circNodeCounter = 0;
	NgSpice &ngspice = NgSpice::getInstance();

	ngspice.Command("circbyline schema");
	for (ACircNode *circNode : m_circNodeArray) {
		circNode->SetId(m_circNodeCounter++);
	}
	for (AComponent *component : m_componentArray) {
		component->SetId(m_componentCounter++);
		UE_LOG(LogTemp, Warning, TEXT("Circuit: %s"), *component->GetCircLine());
		ngspice.Command(TCHAR_TO_ANSI(*(FString("circbyline ") + component->GetCircLine())));
	}
	ngspice.Command("circbyline .end");
	ngspice.Command("tran 100MS 10000MS uic");

	// toto sa tu pridalo
	ngspice.Command("circbyline .end");
	ngspice.Command("bg_run");

	ngspice.setCallbackForResults(indexToCircuitArray);

	//ngspice.Command("destroy all");
	//ngspice.Command("reset");
	//ngspice.Command("setcirc schema");
	//ngspice.Command("remcirc");
}

void ACircuit::Report(const FString& report)
{
	UE_LOG(LogTemp, Warning, TEXT("Report: %s"), *report);
}
