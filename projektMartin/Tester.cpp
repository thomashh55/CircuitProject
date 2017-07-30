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

	// Create ngSpice
	UE_LOG(TesterLog, Warning, TEXT("Tester: Creating"));
	ngspice = new NGSPICE();
	circuit = GetWorld()->SpawnActor<ACircuit>(ACircuit::StaticClass());

	// Assign reporter
	reporter = GetWorld()->SpawnActor<AReporter>(AReporter::StaticClass());
	ngspice->SetReporter(reporter);
	UE_LOG(TesterLog, Warning, TEXT("Tester: Assigning reporter"));

	// initialize ngSpice
	UE_LOG(TesterLog, Warning, TEXT("Tester: Initializing NgSpice"));
	int8 iret = ngspice->Init();
	UE_LOG(TesterLog, Warning, TEXT("Tester: NgSpice initialized"));

	/*AMyActor::Report("Checking IsRunning");
	bool bIsRunning = ngspice->IsRunning();
	AMyActor::Report("IsRunning checked");*/

	// Prepare circuit
	UE_LOG(TesterLog, Warning, TEXT("Tester: Executing commands"));
	
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
	iret = ngspice->Command("circbyline schema 1");
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
	iret = ngspice->Command("circbyline .end");

	// By Tomas
	/*ngspice->Command("circbyline test array");
	ngspice->Command("circbyline V1 1 0 1");
	ngspice->Command("circbyline R1 1 2 1");
	ngspice->Command("circbyline C1 2 0 1 ic=0");
	ngspice->Command("circbyline .tran 0.1 2 uic");
	ngspice->Command("circbyline .end");*/

	UE_LOG(TesterLog, Warning, TEXT("Tester: Commands executed"));

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
	int8 iret = ngspice->Command("bg_run");
}

void ATester::PressedU()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: U Pressed"));
	int8 iret = ngspice->Command("bg_step");
}

void ATester::PressedI()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: I Pressed"));
	int8 iret = ngspice->Command("bg_halt");
}

void ATester::PressedO()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: O Pressed"));
	int8 iret = ngspice->Command("bg_resume");
}

void ATester::PressedP()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: P Pressed"));
	int8 iret = ngspice->Command("reset");
}

void ATester::PressedG()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: G Pressed"));
	int8 iret = ngspice->Command("setscale");
}

void ATester::PressedH()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: H Pressed"));

	char **plots = ngspice->GetAllPlots();
	int8 i = 0;
	while (plots[i] != NULL) {
		UE_LOG(TesterLog, Warning, TEXT("Tester: Plot %d: %s"), i, *FString(plots[i]));
		i++;
	}
}

void ATester::PressedJ()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: J Pressed"));
	FString plotName(ngspice->GetPlotName());
	UE_LOG(TesterLog, Warning, TEXT("Tester: Plot name: %s"), *plotName);

	char **vecs = ngspice->GetAllVecs(TCHAR_TO_ANSI(*plotName));
	int8 i = 0;
	while (vecs[i] != NULL) {
		UE_LOG(TesterLog, Warning, TEXT("Tester: Vec %d: %s"), i, *FString(vecs[i]));
		i++;
	}
}

void ATester::PressedK()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: K Pressed"));
	int8 iret = ngspice->Command("destroy");
}

void ATester::PressedL()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: L Pressed"));
	ngspice->GetVecInfo("V(2)");
}

double time = 0;

void ATester::PressedC()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: C Pressed"));
	time = 1;
	UE_LOG(TesterLog, Warning, TEXT("Tester: Time reset: %f"), time);
}

void ATester::PressedV()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: V Pressed"));
	ngspice->SetBreakpoint(time);
	UE_LOG(TesterLog, Warning, TEXT("Tester: Time set: %f"), time);
	time += 1.0f;
}

void ATester::PressedB()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: B Pressed"));
	int8 iret = ngspice->Command("op");
}

void ATester::PressedN()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: N Pressed"));
	int8 iret = ngspice->Command("dc v1 5 15 1");
}

void ATester::PressedM()
{
	UE_LOG(TesterLog, Warning, TEXT("Tester: M Pressed"));
	int8 iret = ngspice->Command("tran 0.1 2 uic");
}