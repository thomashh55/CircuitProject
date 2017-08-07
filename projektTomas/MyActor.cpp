// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"

int ng_getchar(char* outputreturn, int ident, void* userdata);
int ng_getstat(char* outputreturn, int ident, void* userdata);
int ng_thread_runs(bool noruns, int ident, void* userdata);
int ng_data(pvecvaluesall vdata, int numvecs, int ident, void* userdata);
ControlledExit ng_exit;
SendInitData ng_initdata;

/*
FARPROC ngSpice_Command_handle = NULL;
FARPROC ngSpice_Init_handle = NULL;
HMODULE ngdllhandle = NULL;*/

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

dvec * vectors2[100];	// vektorov bude tolko, kolko bude nodov+1, to sa da vyratat,, plus nemusi sa kazdy uvazovat
int vectorscount2 = 0;

void vypishodnot() {
	// prejst vsetky vektory, ak sa meno zacina na V, tak prejde vsetky nody a najde spravne id,, ak sa zacina na v tak prejde vsetky dummy voltage a najde spravne id

	for (int i = 0; i < vectorscount2; i++) {
		double * vectorvalue = vectors2[i]->v_realdata;
		UE_LOG(LogTemp, Warning, TEXT("tu je vektor zaznamenany a jeho meno je %s\n"), *(FString(vectors2[i]->v_name)));

		/*for (int a = 0; a < vectors[i]->v_length; a++) {
		FString value = FString::SanitizeFloat(vectorvalue[a]);
		UE_LOG(LogTemp, Warning, TEXT("Vector value %d: %s\n"), a, *(value));
		}*/
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	/*int ret = ngSpice_Init(ng_getchar, ng_getstat, ng_exit, ng_data, ng_initdata, ng_thread_runs, NULL);

	ngSpice_Command("circbyline test array");
	ngSpice_Command("circbyline V1 1 0 1");
	ngSpice_Command("circbyline R1 1 2 1");
	ngSpice_Command("circbyline C1 2 0 1 ic=0");
	ngSpice_Command("circbyline .tran 100ms 30000ms");
	ngSpice_Command("circbyline .end");
	ngSpice_Command("bg_run");

	Super::BeginPlay();*/

	//ACircuit *circuit;
	circuit = GetWorld()->SpawnActor<ACircuit>(ACircuit::StaticClass());

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

	circuit->AddWire(GetWorld()->SpawnActor<AWire>(AWire::StaticClass()),
		voltageSource->GetCircNodeArray()[1], resistor1->GetCircNodeArray()[0]);
	circuit->AddWire(GetWorld()->SpawnActor<AWire>(AWire::StaticClass()),
		resistor1->GetCircNodeArray()[1], resistor2->GetCircNodeArray()[0]);
	circuit->AddWire(GetWorld()->SpawnActor<AWire>(AWire::StaticClass()),
		resistor2->GetCircNodeArray()[1], resistor3->GetCircNodeArray()[0]);
	circuit->AddWire(GetWorld()->SpawnActor<AWire>(AWire::StaticClass()),
		resistor3->GetCircNodeArray()[1], voltageSource->GetCircNodeArray()[0]);

	circuit->Start();

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int ng_getchar(char * outputreturn, int ident, void* userdata)
{
	FString s = outputreturn;
	UE_LOG(LogTemp, Warning, TEXT("%s\n"), *s);
	return 0;
}

int ng_getstat(char * outputreturn, int ident, void* userdata)
{
	FString s = outputreturn;
	UE_LOG(LogTemp, Warning, TEXT("%s\n"), *s);
	return 0;
}

bool wasrunning2 = false;
int ng_thread_runs(bool noruns, int ident, void* userdata)
{
	if (noruns) {
		UE_LOG(LogTemp, Warning, TEXT("bg not running\n"));

		if (wasrunning2 == true) {
			vypishodnot();
		}

		wasrunning2 = false;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("bg running\n"));
		wasrunning2 = true;
	}
	return 0;
}

int ng_exit(int exitstatus, bool immediate, bool quitexit, int ident, void* userdata)
{
	if (quitexit) {
		UE_LOG(LogTemp, Warning, TEXT("DNote: Returned from quit with exit status %d\n"), exitstatus);
	}
	if (immediate) {
		UE_LOG(LogTemp, Warning, TEXT("DNote: Unload ngspice\n"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("DNote: Prepare unloading ngspice\n"));
	}
	return exitstatus;
}
/*
int ng_initdata(pvecinfoall intdata, int ident, void* userdata)
{
	FString name = intdata->name;
	UE_LOG(LogTemp, Warning, TEXT("Name of the plot: %s"), *(name));

	FString title = intdata->title;
	UE_LOG(LogTemp, Warning, TEXT("Title of the plot: %s"), *(title));

	FString date = intdata->date;
	UE_LOG(LogTemp, Warning, TEXT("Date of the plot: %s"), *(date));

	FString type = intdata->type;
	UE_LOG(LogTemp, Warning, TEXT("Type of the plot: %s\n"), *(type));

	vectorscount2 = intdata->veccount;
	for (int i = 0; i < vectorscount; i++) {
		UE_LOG(LogTemp, Warning, TEXT("Vector number: %d"), i);

		FString vecname = intdata->vecs[i]->vecname;
		UE_LOG(LogTemp, Warning, TEXT("Vector name: %s\n"), *(vecname));

		vectors[i] = (dvec*)intdata->vecs[i]->pdvec;

		FString vectorname = vector->v_name;
		UE_LOG(LogTemp, Warning, TEXT("Vector name: %s\n"), *(vectorname));

		double * vectorvalue = vector->v_realdata;

		for (int i = 0; i < vector->v_length; i++) {
		FString value = FString::SanitizeFloat(vectorvalue[i]);
		UE_LOG(LogTemp, Warning, TEXT("Vector value %d: %s\n"),i , *(value));
		}
	}

	return 0;
}

int ng_data(pvecvaluesall vdata, int numvecs, int ident, void* userdata)
{
	int i;
	for (i = 0; i < numvecs; i++) {
	//UE_LOG(LogTemp, Warning, TEXT("tu sa vektor vypisuje data"));
	FString name = vdata->vecsa[i]->name;
	FString value = FString::SanitizeFloat(vdata->vecsa[i]->creal);
	UE_LOG(LogTemp, Warning, TEXT("Vector: %s a jeho hodnota: %s\n"), *(name), *(value));
	}

	return 0;
}*/