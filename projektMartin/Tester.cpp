// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Tester.h"

//Tester Log
DEFINE_LOG_CATEGORY(TesterLog);

// Sets default values
ATester::ATester()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATester::BeginPlay()
{
	Super::BeginPlay();

	// Prepare controlls
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	EnableInput(PlayerController);
	InputComponent->BindKey(EKeys::Y, IE_Released, this, &ATester::PressedY);
	InputComponent->BindKey(EKeys::U, IE_Released, this, &ATester::PressedU);
	InputComponent->BindKey(EKeys::I, IE_Released, this, &ATester::PressedI);
	InputComponent->BindKey(EKeys::O, IE_Released, this, &ATester::PressedO);
	InputComponent->BindKey(EKeys::P, IE_Released, this, &ATester::PressedP);

	InputComponent->BindKey(EKeys::G, IE_Released, this, &ATester::PressedG);
	InputComponent->BindKey(EKeys::H, IE_Released, this, &ATester::PressedH);
	InputComponent->BindKey(EKeys::J, IE_Released, this, &ATester::PressedJ);
	InputComponent->BindKey(EKeys::K, IE_Released, this, &ATester::PressedK);
	InputComponent->BindKey(EKeys::L, IE_Released, this, &ATester::PressedL);

	InputComponent->BindKey(EKeys::C, IE_Released, this, &ATester::PressedC);
	InputComponent->BindKey(EKeys::V, IE_Released, this, &ATester::PressedV);
	InputComponent->BindKey(EKeys::B, IE_Released, this, &ATester::PressedB);
	InputComponent->BindKey(EKeys::N, IE_Released, this, &ATester::PressedN);
	InputComponent->BindKey(EKeys::M, IE_Released, this, &ATester::PressedM);

	// Assign reporter
	/*reporter = GetWorld()->SpawnActor<AReporter>(AReporter::StaticClass());
	ngspice->SetReporter(reporter);
	UE_LOG(TesterLog, Warning, TEXT("Tester: Assigning reporter"));

	// initialize ngSpice
	UE_LOG(TesterLog, Warning, TEXT("Tester: Initializing NgSpice"));
	int8 iret = ngspice->Init();
	UE_LOG(TesterLog, Warning, TEXT("Tester: NgSpice initialized"));*/

	/*AMyActor::Report("Checking IsRunning");
	bool bIsRunning = ngspice->IsRunning();
	AMyActor::Report("IsRunning checked");*/

	// Prepare circuit
	//UE_LOG(TesterLog, Warning, TEXT("Tester: Executing commands"));
	
	// Serial resistors
	/*iret = ngspice->Command("circbyline fail test");
	iret = ngspice->Command("circbyline V1 0 1 9");
	iret = ngspice->Command("circbyline R1 1 2 3");
	iret = ngspice->Command("circbyline R2 2 3 10");
	iret = ngspice->Command("circbyline R3 3 0 5");
	//iret = ngspice->Command("circbyline .tran 1 20 uic");
	//iret = ngspice->Command("circbyline .dc v1 5 15 1");
	iret = ngspice->Command("circbyline .end");*/

	/*NgSpice::getInstance().Command("circbyline serial resistors");
	NgSpice::getInstance().Command("circbyline V1 0 1 9");
	NgSpice::getInstance().Command("circbyline R2 2 3 3");
	NgSpice::getInstance().Command("circbyline R3 4 5 10");
	NgSpice::getInstance().Command("circbyline R4 6 7 5");
	NgSpice::getInstance().Command("circbyline V5 1 2 0");
	NgSpice::getInstance().Command("circbyline V6 3 4 0");
	NgSpice::getInstance().Command("circbyline V7 5 6 0");
	NgSpice::getInstance().Command("circbyline V8 7 0 0");
	NgSpice::getInstance().Command("circbyline .end");*/
	//NgSpice::getInstance().Command("tran 0.01 10 uic");

	// Parallel ampermeter test
	/*iret = ngspice->Command("circbyline ampermeter test");
	iret = ngspice->Command("circbyline V1 0 1 20");
	iret = ngspice->Command("circbyline V2 1 2 0");
	//iret = ngspice->Command("circbyline R1 2 3 1");
	iret = ngspice->Command("circbyline V3 1 4 0");
	//iret = ngspice->Command("circbyline R2 4 3 1");
	iret = ngspice->Command("circbyline R3 3 0 10");
	iret = ngspice->Command("circbyline .end");*/

	// Schema 1
	/*iret = ngspice->Command("circbyline schema 1");
	iret = ngspice->Command("circbyline V1 1 0 9");
	//iret = ngspice->Command("circbyline D2 1 2");
	//iret = ngspice->Command("circbyline D3 1 3");
	iret = ngspice->Command("circbyline R4 1 4 100"); //2 4
	iret = ngspice->Command("circbyline R5 1 5 100");
	iret = ngspice->Command("circbyline R6 1 6 100");
	iret = ngspice->Command("circbyline R7 1 7 100"); //3 7
	iret = ngspice->Command("circbyline C8 4 5 1000U ic=1V");
	iret = ngspice->Command("circbyline C9 7 6 1000U");
	iret = ngspice->Command("circbyline Q10 4 6 0");
	iret = ngspice->Command("circbyline Q11 7 5 0");
	iret = ngspice->Command("circbyline .end");*/

	// By Tomas
	/*ngspice->Command("circbyline test array");
	ngspice->Command("circbyline V1 1 0 1");
	ngspice->Command("circbyline R1 1 2 1");
	ngspice->Command("circbyline C1 2 0 1 ic=0");
	ngspice->Command("circbyline .tran 0.1 2 uic");
	ngspice->Command("circbyline .end");*/

	//UE_LOG(TesterLog, Warning, TEXT("Tester: Commands executed"));

	/*int8 a = MathFuncs::MyMathFuncs::Add(5, 10);
	UE_LOG(MyActorLog, Warning, TEXT("Add %d %d"), MathFuncs::MyMathFuncs::Add(5, 10), a);

	int8 aa = 5;
	aa = getIntPlusPlus(aa);
	UE_LOG(MyActorLog, Warning, TEXT("PlusPlus %d"), aa);*/
}

// Called every frame
void ATester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATester::PressedY()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: Y Pressed"));

	// Serial resistors

	// Create circuit
	UE_LOG(TesterLog, Warning, TEXT("Tester: Creating circuit"));
	t0_circuit = GetWorld()->SpawnActor<ACircuit>(ACircuit::StaticClass());
	UE_LOG(TesterLog, Warning, TEXT("Tester: Circuit created"));

	UE_LOG(TesterLog, Warning, TEXT("Tester: Creating nodes and components for serial resistors test"));

	t0_voltageSource1 = GetWorld()->SpawnActor<AVoltageSource>(AVoltageSource::StaticClass());
	t0_voltageSource1->SetDirectCurrent(9);
	t0_circuit->AddComponent(t0_voltageSource1);

	t0_resistor1 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	t0_resistor1->SetResistance(3);
	t0_circuit->AddComponent(t0_resistor1);

	t0_resistor2 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	t0_resistor2->SetResistance(10);
	t0_circuit->AddComponent(t0_resistor2);

	t0_resistor3 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	t0_resistor3->SetResistance(5);
	t0_circuit->AddComponent(t0_resistor3);

	t0_wire1 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t0_circuit->AddWire(t0_wire1, t0_voltageSource1->GetCircNodeArray()[1], t0_resistor1->GetCircNodeArray()[0]);

	t0_wire2 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t0_circuit->AddWire(t0_wire2, t0_resistor1->GetCircNodeArray()[1], t0_resistor2->GetCircNodeArray()[0]);

	t0_wire3 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t0_circuit->AddWire(t0_wire3, t0_resistor2->GetCircNodeArray()[1], t0_resistor3->GetCircNodeArray()[0]);

	t0_wire4 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t0_circuit->AddWire(t0_wire4, t0_resistor3->GetCircNodeArray()[1], t0_voltageSource1->GetCircNodeArray()[0]);

	UE_LOG(TesterLog, Warning, TEXT("Tester: Nodes and components created"));
}

void ATester::PressedU()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: U Pressed"));

	// Schema 1

	// Create circuit
	UE_LOG(TesterLog, Warning, TEXT("Tester: Creating circuit"));
	t1_circuit = GetWorld()->SpawnActor<ACircuit>(ACircuit::StaticClass());
	UE_LOG(TesterLog, Warning, TEXT("Tester: Circuit created"));

	UE_LOG(TesterLog, Warning, TEXT("Tester: Creating nodes and components for schema 1"));

	t1_voltageSource1 = GetWorld()->SpawnActor<AVoltageSource>(AVoltageSource::StaticClass());
	t1_voltageSource1->SetDirectCurrent(3.7);
	t1_circuit->AddComponent(t1_voltageSource1);

	t1_diode1 = GetWorld()->SpawnActor<ADiode>(ADiode::StaticClass());
	t1_circuit->AddComponent(t1_diode1);

	t1_diode2 = GetWorld()->SpawnActor<ADiode>(ADiode::StaticClass());
	t1_circuit->AddComponent(t1_diode2);

	t1_resistor1 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	t1_resistor1->SetResistance(1000);
	t1_circuit->AddComponent(t1_resistor1);

	t1_resistor2 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	t1_resistor2->SetResistance(5000);
	t1_circuit->AddComponent(t1_resistor2);

	t1_resistor3 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	t1_resistor3->SetResistance(5000);
	t1_circuit->AddComponent(t1_resistor3);

	t1_resistor4 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	t1_resistor4->SetResistance(1000);
	t1_circuit->AddComponent(t1_resistor4);

	t1_capacitor1 = GetWorld()->SpawnActor<ACapacitor>(ACapacitor::StaticClass());
	t1_capacitor1->SetCapacitance(0.0022);
	t1_capacitor1->SetInitVoltage(1);
	t1_circuit->AddComponent(t1_capacitor1);

	t1_capacitor2 = GetWorld()->SpawnActor<ACapacitor>(ACapacitor::StaticClass());
	t1_capacitor2->SetCapacitance(0.0022);
	t1_circuit->AddComponent(t1_capacitor2);

	t1_transistor1 = GetWorld()->SpawnActor<ATransistor>(ATransistor::StaticClass());
	t1_circuit->AddComponent(t1_transistor1);

	t1_transistor2 = GetWorld()->SpawnActor<ATransistor>(ATransistor::StaticClass());
	t1_circuit->AddComponent(t1_transistor2);

	t1_wire1 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire1, t1_voltageSource1->GetCircNodeArray()[0], t1_diode1->GetCircNodeArray()[0]);

	t1_wire2 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire2, t1_voltageSource1->GetCircNodeArray()[0], t1_resistor2->GetCircNodeArray()[0]);

	t1_wire3 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire3, t1_voltageSource1->GetCircNodeArray()[0], t1_resistor3->GetCircNodeArray()[0]);

	t1_wire4 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire4, t1_voltageSource1->GetCircNodeArray()[0], t1_diode2->GetCircNodeArray()[0]);

	t1_wire5 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire5, t1_diode1->GetCircNodeArray()[1], t1_resistor1->GetCircNodeArray()[0]);

	t1_wire6 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire6, t1_diode2->GetCircNodeArray()[1], t1_resistor4->GetCircNodeArray()[0]);

	t1_wire7 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire7, t1_resistor1->GetCircNodeArray()[1], t1_transistor1->GetCircNodeArray()[0]);

	t1_wire8 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire8, t1_resistor1->GetCircNodeArray()[1], t1_capacitor1->GetCircNodeArray()[0]);

	t1_wire9 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire9, t1_resistor2->GetCircNodeArray()[1], t1_capacitor1->GetCircNodeArray()[1]);

	t1_wire10 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire10, t1_resistor2->GetCircNodeArray()[1], t1_transistor2->GetCircNodeArray()[1]);

	t1_wire11 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire11, t1_resistor3->GetCircNodeArray()[1], t1_transistor1->GetCircNodeArray()[1]);

	t1_wire12 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire12, t1_resistor3->GetCircNodeArray()[1], t1_capacitor2->GetCircNodeArray()[1]);

	t1_wire13 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire13, t1_resistor4->GetCircNodeArray()[1], t1_capacitor2->GetCircNodeArray()[0]);

	t1_wire14 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire14, t1_resistor4->GetCircNodeArray()[1], t1_transistor2->GetCircNodeArray()[0]);

	t1_wire15 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire15, t1_transistor1->GetCircNodeArray()[2], t1_voltageSource1->GetCircNodeArray()[1]);

	t1_wire16 = GetWorld()->SpawnActor<AWire>(AWire::StaticClass());
	t1_circuit->AddWire(t1_wire16, t1_transistor2->GetCircNodeArray()[2], t1_voltageSource1->GetCircNodeArray()[1]);

	UE_LOG(TesterLog, Warning, TEXT("Tester: Nodes and components created"));
}

void ATester::PressedI()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: I Pressed"));
}

void ATester::PressedO()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: O Pressed"));
}

void ATester::PressedP()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: P Pressed"));
	//int8 iret = circuit->Command("bg_run");
	//int8 iret = circuit->Command("bg_step");
	//int8 iret = circuit->Command("bg_halt");
	//int8 iret = circuit->Command("bg_resume");
	//int8 iret = circuit->Command("bg_reset");
	//ngspice->GetVecInfo("V(2)");
}

void ATester::PressedG()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: G Pressed"));

	UE_LOG(TesterLog, Warning, TEXT("Tester: Real time: %f"), t0_circuit->GetRealTime());
	UE_LOG(TesterLog, Warning, TEXT("Tester: Simulation time: %f"), t0_circuit->GetSimulationTime());

	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire1 current: %f"), t0_circuit->MeasureCurrent(t0_wire1));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire1 voltage: %f"), t0_circuit->MeasureVoltage(t0_wire1->GetCircNodeArray()[0], t0_wire1->GetCircNodeArray()[0]));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire1 current at time = 5: %f"), t0_circuit->MeasureCurrent(t0_wire1, 5));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire1 voltage at time = 5: %f"), t0_circuit->MeasureVoltage(t0_wire1->GetCircNodeArray()[0], t0_wire1->GetCircNodeArray()[0], 5));
	
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire2 current: %f"), t0_circuit->MeasureCurrent(t0_wire2));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire2 voltage: %f"), t0_circuit->MeasureVoltage(t0_wire2->GetCircNodeArray()[0], t0_wire1->GetCircNodeArray()[0]));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire2 current at time = 5: %f"), t0_circuit->MeasureCurrent(t0_wire2, 5));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire2 voltage at time = 5: %f"), t0_circuit->MeasureVoltage(t0_wire2->GetCircNodeArray()[0], t0_wire1->GetCircNodeArray()[0], 5));

	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire3 current: %f"), t0_circuit->MeasureCurrent(t0_wire3));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire3 voltage: %f"), t0_circuit->MeasureVoltage(t0_wire3->GetCircNodeArray()[0], t0_wire1->GetCircNodeArray()[0]));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire3 current at time = 5: %f"), t0_circuit->MeasureCurrent(t0_wire3, 5));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire3 voltage at time = 5: %f"), t0_circuit->MeasureVoltage(t0_wire3->GetCircNodeArray()[0], t0_wire1->GetCircNodeArray()[0], 5));

	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire4 current: %f"), t0_circuit->MeasureCurrent(t0_wire4));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire4 voltage: %f"), t0_circuit->MeasureVoltage(t0_wire4->GetCircNodeArray()[0], t0_wire1->GetCircNodeArray()[0]));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire4 current at time = 5: %f"), t0_circuit->MeasureCurrent(t0_wire4, 5));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Wire4 voltage at time = 5: %f"), t0_circuit->MeasureVoltage(t0_wire4->GetCircNodeArray()[0], t0_wire1->GetCircNodeArray()[0], 5));

}

void ATester::PressedH()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: H Pressed"));

	UE_LOG(TesterLog, Warning, TEXT("Tester: Real time: %f"), t1_circuit->GetRealTime());
	UE_LOG(TesterLog, Warning, TEXT("Tester: Simulation time: %f"), t1_circuit->GetSimulationTime());

	UE_LOG(TesterLog, Warning, TEXT("Tester: MB1 voltage: %f"), t1_circuit->MeasureVoltage(t1_transistor1->GetCircNodeArray()[1], t1_voltageSource1->GetCircNodeArray()[1]));
	UE_LOG(TesterLog, Warning, TEXT("Tester: MB2 voltage: %f"), t1_circuit->MeasureVoltage(t1_transistor2->GetCircNodeArray()[1], t1_voltageSource1->GetCircNodeArray()[1]));
	UE_LOG(TesterLog, Warning, TEXT("Tester: MB3 voltage: %f"), t1_circuit->MeasureVoltage(t1_transistor1->GetCircNodeArray()[0], t1_voltageSource1->GetCircNodeArray()[1]));
	UE_LOG(TesterLog, Warning, TEXT("Tester: MB4 voltage: %f"), t1_circuit->MeasureVoltage(t1_transistor2->GetCircNodeArray()[0], t1_voltageSource1->GetCircNodeArray()[1]));

	UE_LOG(TesterLog, Warning, TEXT("Tester: Ce1 current: %f"), t1_circuit->MeasureCurrent(t1_wire15));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Ce2 current: %f"), t1_circuit->MeasureCurrent(t1_wire16));
	UE_LOG(TesterLog, Warning, TEXT("Tester: B1 current: %f"), t1_circuit->MeasureCurrent(t1_wire11));
	UE_LOG(TesterLog, Warning, TEXT("Tester: B2 current: %f"), t1_circuit->MeasureCurrent(t1_wire10));
	
}

void ATester::PressedJ()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: J Pressed"));
}

void ATester::PressedK()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: K Pressed"));
	//NgSpice::getInstance().Command("remcirc");
}

void ATester::PressedL()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: L Pressed"));
	NgSpice::getInstance().Command("destroy");
}

void ATester::PressedC()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: C Pressed"));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Starting simulation serial resistors"));
	if (t0_circuit->Start(100)) {
		UE_LOG(TesterLog, Warning, TEXT("Tester: Simulation serial resistors started"));
	}
}

void ATester::PressedV()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: V Pressed"));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Starting simulation schema 1"));
	if (t1_circuit->Start(100)) {
		UE_LOG(TesterLog, Warning, TEXT("Tester: Simulation schema 1 started"));
	}
}

void ATester::PressedB()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: B Pressed"));
}

void ATester::PressedN()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: N Pressed"));

	char **plots = NgSpice::getInstance().GetAllPlots();
	int i = 0;
	while (plots[i] != NULL) {
		UE_LOG(TesterLog, Warning, TEXT("Tester: Plot %d: %s"), i, *FString(plots[i]));
		i++;
	}
}

void ATester::PressedM()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: M Pressed"));
	FString plotName(NgSpice::getInstance().GetPlotName());
	UE_LOG(TesterLog, Warning, TEXT("Tester: Plot name: %s"), *plotName);

	char **vecs = NgSpice::getInstance().GetAllVecs(TCHAR_TO_ANSI(*plotName));
	int i = 0;
	while (vecs[i] != NULL) {
		UE_LOG(TesterLog, Warning, TEXT("Tester: Vec %d: %s"), i, *FString(vecs[i]));
		i++;
	}
}