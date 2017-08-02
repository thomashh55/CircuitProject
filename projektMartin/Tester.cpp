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

	// Create circuit
	UE_LOG(TesterLog, Warning, TEXT("Tester: Creating circuit"));
	circuit = GetWorld()->SpawnActor<ACircuit>(ACircuit::StaticClass());
	UE_LOG(TesterLog, Warning, TEXT("Tester: Circuit created"));

	UE_LOG(TesterLog, Warning, TEXT("Tester: Creating nodes and components"));

	AVoltageSource *voltageSource = GetWorld()->SpawnActor<AVoltageSource>(AVoltageSource::StaticClass());
	voltageSource->SetDirectCurrent(9);
	circuit->AddComponent(voltageSource);

	AResistor *resistor1 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	resistor1->SetResistance(3);
	circuit->AddComponent(resistor1);

	AResistor *resistor2 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	resistor2->SetResistance(10);
	circuit->AddComponent(resistor2);

	AResistor *resistor3 = GetWorld()->SpawnActor<AResistor>(AResistor::StaticClass());
	resistor3->SetResistance(5);
	circuit->AddComponent(resistor3);

	GetWorld()->SpawnActor<AReporter>(AReporter::StaticClass())->Report(FString::SanitizeFloat(9));

	circuit->AddWire(GetWorld()->SpawnActor<AWire>(AWire::StaticClass()),
		voltageSource->GetCircNodeArray()[1], resistor1->GetCircNodeArray()[0]);
	circuit->AddWire(GetWorld()->SpawnActor<AWire>(AWire::StaticClass()),
		resistor1->GetCircNodeArray()[1], resistor2->GetCircNodeArray()[0]);
	circuit->AddWire(GetWorld()->SpawnActor<AWire>(AWire::StaticClass()),
		resistor2->GetCircNodeArray()[1], resistor3->GetCircNodeArray()[0]);
	circuit->AddWire(GetWorld()->SpawnActor<AWire>(AWire::StaticClass()),
		resistor3->GetCircNodeArray()[1], voltageSource->GetCircNodeArray()[0]);

	UE_LOG(TesterLog, Warning, TEXT("Tester: Nodes and components created"));
}

void ATester::PressedU()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: U Pressed"));
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
	NgSpice::getInstance().SetReporter(GetWorld()->SpawnActor<AReporter>(AReporter::StaticClass()));
	NgSpice::getInstance().Command("circbyline test");
	NgSpice::getInstance().Command("circbyline V1 0 1 9");
	NgSpice::getInstance().Command("circbyline R2 2 3 3");
	NgSpice::getInstance().Command("circbyline R3 4 5 10");
	NgSpice::getInstance().Command("circbyline R4 6 7 5");
	NgSpice::getInstance().Command("circbyline V5 1 2 0");
	NgSpice::getInstance().Command("circbyline V6 3 4 0");
	NgSpice::getInstance().Command("circbyline V7 5 6 0");
	NgSpice::getInstance().Command("circbyline V8 7 0 0");
	NgSpice::getInstance().Command("circbyline .end");
	NgSpice::getInstance().Command("tran 0.1 2 uic");
}

void ATester::PressedH()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: H Pressed"));
}

void ATester::PressedJ()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: J Pressed"));
}

void ATester::PressedK()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: K Pressed"));
}

void ATester::PressedL()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: L Pressed"));
	NgSpice::getInstance().Command("destroy");
}

void ATester::PressedC()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: C Pressed"));
	UE_LOG(TesterLog, Warning, TEXT("Tester: Starting simulation"));
	circuit->Start();
	UE_LOG(TesterLog, Warning, TEXT("Tester: Simulation started"));
}

void ATester::PressedV()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: V Pressed"));
}

void ATester::PressedB()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: B Pressed"));
}

void ATester::PressedN()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: N Pressed"));

	char **plots = NgSpice::getInstance().GetAllPlots();
	int8 i = 0;
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
	int8 i = 0;
	while (vecs[i] != NULL) {
		UE_LOG(TesterLog, Warning, TEXT("Tester: Vec %d: %s"), i, *FString(vecs[i]));
		i++;
	}
}