// Martin Gulis & Tomas Liscak

#include "CoreMinimal.h"

#include "Circuit.h"


// Circuit Log
DEFINE_LOG_CATEGORY(CircuitLog);

// Sets default values
ACircuit::ACircuit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACircuit::BeginPlay()
{
	Super::BeginPlay();

	// Reset
	m_componentArray.Empty();
	m_wireArray.Empty();
	m_circNodeArray.Empty();

	m_timeArray.Empty();
	m_endTime = 0;
	m_realTime = 0;
	m_realTimeIndex = 0;
	m_bIsRunning = false;

	m_errorCircNode = NULL;
	m_errorWire = NULL;
}

// Called every frame
void ACircuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Adds time
	if (m_bIsRunning) {
		m_realTime += DeltaTime;
		while (m_realTimeIndex < m_timeArray.Num() - 1 && m_timeArray[m_realTimeIndex + 1] <= m_realTime) {
			m_realTimeIndex++;
			//UE_LOG(CircuitLog, Warning, TEXT("Circuit: Time: %f ArrayTime: %f index: %d"), m_realTime, m_timeArray[m_realTimeIndex], m_realTimeIndex);
		}

		// Stop simulation
		if (m_realTime >= m_endTime) {
			m_bIsRunning = false;
			//UE_LOG(CircuitLog, Warning, TEXT("Circuit: %f seconds passed"), m_endTime);
		}
	}
}

// Initialize NgSpice
void ACircuit::Init()
{
	NgSpice::getInstance().Init();
}

// Adds component to the circuit
void ACircuit::AddComp(AComponent *component)
{
	m_componentArray.Add(component);
	for (ACircNode *node : component->GetCircNodeArray()) {
		m_circNodeArray.Add(node);
	}
}

// Removes component from the circuit
void ACircuit::RemoveComp(AComponent *component)
{
	m_componentArray.Remove(component);

	// Find wires to delete
	TArray<AWire*> wireToDelete;
	TArray<ACircNode*> circNodeToDelete;
	for (AWire *wire : m_wireArray) {
		bool bShouldDelete = false;
		for (ACircNode *circnode1 : wire->GetCircNodeArray()) {
			for (ACircNode *circnode2 : component->GetCircNodeArray()) {
				if (circnode1 == circnode2) {
					bShouldDelete = true;
					circNodeToDelete.Add(circnode1);
				}
			}
		}
		if (bShouldDelete) {
			wireToDelete.Add(wire);
		}
	}

	// Delete wires and nodes
	for (AWire *wire : wireToDelete) {
		m_wireArray.Remove(wire);
	}
	for (ACircNode *circnode : circNodeToDelete) {
		m_circNodeArray.Remove(circnode);
	}
}

// Adds wires to the circuit
void ACircuit::AddWire(AWire *wire, ACircNode *circNode1, ACircNode *circNode2)
{
	m_wireArray.Add(wire);
	wire->AddCircNodes(circNode1, circNode2);
}

// Remove wires from the circuit
void ACircuit::RemoveWire(AWire *wire)
{
	m_wireArray.Remove(wire);
}

// Get array of components
TArray<AComponent*> ACircuit::GetComponentArray()
{
	return m_componentArray;
}

// Get array of wires
TArray<AWire*> ACircuit::GetWireArray()
{
	return m_wireArray;
}

// Simulation commands
bool ACircuit::Start(float endTime)
{
	NgSpice &ngspice = NgSpice::getInstance();
	int m_componentCounter = 0;
	int m_circNodeCounter = 0;

	if (endTime < 0) {
		endTime = 0;
	}

	// Reset time and start simulation
	bool bCanRun = ngspice.AddCircuit(this);
	if (bCanRun) {
		m_timeArray.Empty();
		m_endTime = endTime;
		m_realTime = 0;
		m_realTimeIndex = 0;
		m_bIsRunning = true;
		m_errorCircNode = NULL;
		m_errorWire = NULL;

		ngspice.Command("circbyline schema");
		/*UE_LOG(CircuitLog, Warning, TEXT("Circuit: Number of nodes: %d"), m_circNodeArray.Num());
		UE_LOG(CircuitLog, Warning, TEXT("Circuit: Number of components: %d"), m_componentArray.Num());
		UE_LOG(CircuitLog, Warning, TEXT("Circuit: Number of wires: %d"), m_wireArray.Num());*/
		for (ACircNode *circNode : m_circNodeArray) {
			circNode->ResetVoltageArray();
			circNode->SetId(m_circNodeCounter++);
		}
		for (AComponent *component : m_componentArray) {
			if (!component->IsA(ANodeComponent::StaticClass())) {
				component->SetId(m_componentCounter++);
				//UE_LOG(CircuitLog, Warning, TEXT("Circuit: %s"), *component->GetCircLine());
				ngspice.Command(TCHAR_TO_ANSI(*(FString("circbyline ") + component->GetCircLine())));
			}
		}
		for (AWire *wire : m_wireArray) {
			wire->ResetCurrentArray();
			wire->SetId(m_componentCounter++);
			//UE_LOG(CircuitLog, Warning, TEXT("Circuit: %s"), *wire->GetCircLine());
			ngspice.Command(TCHAR_TO_ANSI(*(FString("circbyline ") + wire->GetCircLine())));
		}
		ngspice.Command(TCHAR_TO_ANSI(*(FString("circbyline .tran 0.01 ") + 
			FString::SanitizeFloat(endTime) + FString(" uic"))));
		ngspice.Command("circbyline .model QNPN npn");
		ngspice.Command("circbyline .model D d");
		ngspice.Command("circbyline .options reltol=0.003");
		ngspice.Command("circbyline .end");
		ngspice.Command("bg_run");
	}
	return bCanRun;
}

bool ACircuit::Stop()
{
	m_bIsRunning = false;
	return true;
}

bool ACircuit::Resume()
{
	m_bIsRunning = true;
	return true;
}

bool ACircuit::ForceStop()
{
	NgSpice &ngspice = NgSpice::getInstance();
	ngspice.Command("bg_halt");
	return true;
}

float ACircuit::GetRealTime()
{
	return m_realTime;
}

float ACircuit::GetSimulationTime()
{
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	return m_timeArray[m_realTimeIndex];
}

// Updates results in components
void ACircuit::FillResults(pvecvaluesall data)
{
	//UE_LOG(CircuitLog, Warning, TEXT("Circuit: data %d arrived"), data->vecindex);
	for (int i = 0; i < data->veccount; i++) {
		if (data->vecsa[i]->name[1] == '(') {
			for (ACircNode *circNode : m_circNodeArray) {
				FString id = FString("V(") + FString::FromInt(circNode->GetId()) + FString(")");
				if (id.Equals(data->vecsa[i]->name, ESearchCase::IgnoreCase)) {
					circNode->AddVoltage(data->vecsa[i]->creal);
					break;
				}
			}
		}
		else if (FString("time").Equals(data->vecsa[i]->name, ESearchCase::IgnoreCase)) {
			m_timeArray.Add(data->vecsa[i]->creal);
		}
		else {
			for (AWire *wire : m_wireArray) {
				FString id = wire->GetId() + FString("#branch");
				if (id.Equals(data->vecsa[i]->name, ESearchCase::IgnoreCase)) {
					wire->AddCurrent(data->vecsa[i]->creal);
					break;
				}
			}
		}
	}
}

// Measure functions for multimeter
/*float ACircuit::MeasureCurrent(AWire *wire, float time) {
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	for (int i = 0; i < m_timeArray.Num() - 1; i++) {
		if (m_timeArray[i + 1] > time) {
			return wire->GetCurrent(i);
		}
	}
	return wire->GetCurrent(m_timeArray.Num() - 1);
}*/

float ACircuit::MeasureCurrent(AWire *wire) {
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	return wire->GetCurrent(m_realTimeIndex);
}

/*float ACircuit::MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2, float time) {
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	for (int i = 0; i < m_timeArray.Num() - 1; i++) {
		if (m_timeArray[i + 1] > time) {
			return circNode1->GetVoltage(i) - circNode2->GetVoltage(i);
		}
	}
	return circNode1->GetVoltage(m_timeArray.Num() - 1) - circNode2->GetVoltage(m_timeArray.Num() - 1);
}*/

float ACircuit::MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2) {
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	return circNode1->GetVoltage(m_realTimeIndex) - circNode2->GetVoltage(m_realTimeIndex);
}

// Updates error in circuit
void ACircuit::FillError(FString error)
{
	// Stop simulation
	m_bIsRunning = false;

	// Find error nodes and wires
	if (error[0] == 'v' || error[0] == 'V') {
		for (AWire *wire : m_wireArray) {
			FString id = wire->GetId() + FString("#branch");
			if (id.Equals(error, ESearchCase::IgnoreCase)) {
				m_errorWire = wire;
				break;
			}
		}
	}
	else {
		for (ACircNode *circNode : m_circNodeArray) {
			FString id = FString::FromInt(circNode->GetId());
			if (id.Equals(error, ESearchCase::IgnoreCase)) {
				m_errorCircNode = circNode;
				break;
			}
		}
	}
}

// Returns error node from circuit
ACircNode *ACircuit::GetErrorCircNode()
{
	return m_errorCircNode;
}

// Returns error wire from circuit
AWire *ACircuit::GetErrorWire()
{
	return m_errorWire;
}

void ACircuit::Report(const FString& report)
{
	UE_LOG(CircuitLog, Warning, TEXT("Report: %s"), *report);
}
