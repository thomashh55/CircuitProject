// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "ngspice/sharedspice.h"
#include "ngspice/dvec.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sstream>

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

dvec * vectors[100];	// vektorov bude tolko, kolko bude nodov+1, to sa da vyratat,, plus nemusi sa kazdy uvazovat
int vectorscount = 0;

void vypishodnot() {
	for (int i = 0; i < vectorscount; i++) {
		double * vectorvalue = vectors[i]->v_realdata;
		UE_LOG(LogTemp, Warning, TEXT("tu je vektor zaznamenany a jeho dlzka je %d\n"), vectors[i]->v_length);
		
		/*for (int a = 0; a < vectors[i]->v_length; a++) {
			FString value = FString::SanitizeFloat(vectorvalue[a]);
			UE_LOG(LogTemp, Warning, TEXT("Vector value %d: %s\n"), a, *(value));
		}*/
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{/*
	ngdllhandle = LoadLibraryA("C:\\Users\\Tomas\\Documents\\Unreal Projects\\MyProject2\\Binaries\\Win64\\ngspice.dll");
	
	if (!ngdllhandle) {
		UE_LOG(LogTemp, Warning, TEXT("nejde nacitat kniznicu"));
	}
	
	ngSpice_Init_handle = GetProcAddress(ngdllhandle, "ngSpice_Init");
	ngSpice_Command_handle = GetProcAddress(ngdllhandle, "ngSpice_Command");

	int * ret = ((int * (*)(SendChar*, SendStat*, ControlledExit*, SendData*, SendInitData*,
		BGThreadRunning*, void*)) ngSpice_Init_handle)(ng_getchar, ng_getstat,
			ng_exit, NULL, ng_initdata, ng_thread_runs, NULL);

	//UE_LOG(LogTemp, Warning, TEXT("%d"), *ret);
	
	ret = ((int * (*)(char*)) ngSpice_Command_handle)("circbyline fail test");
	ret = ((int * (*)(char*)) ngSpice_Command_handle)("circbyline V1 1 0 1");
	ret = ((int * (*)(char*)) ngSpice_Command_handle)("circbyline R1 1 0 1");
	ret = ((int * (*)(char*)) ngSpice_Command_handle)("circbyline .include xyz");
	ret = ((int * (*)(char*)) ngSpice_Command_handle)("circbyline .dc V1 0 1 0.1");
	ret = ((int * (*)(char*)) ngSpice_Command_handle)("circbyline .end");
	
	Sleep(100);

	ret = ((int * (*)(char*)) ngSpice_Command_handle)("bg_run");*/

	int ret = ngSpice_Init(ng_getchar, ng_getstat, ng_exit, ng_data, ng_initdata, ng_thread_runs, NULL);

	ngSpice_Command("circbyline test array");
	ngSpice_Command("circbyline V1 1 0 1");
	ngSpice_Command("circbyline R1 1 2 1");
	ngSpice_Command("circbyline C1 2 0 1 ic=0");
	ngSpice_Command("circbyline .tran 100ms 30000ms");
	ngSpice_Command("circbyline .end");
	ngSpice_Command("bg_run");
	
	//UE_LOG(LogTemp, Warning, TEXT("\nCurrent plot is %s\n\n"), *(ngSpice_CurPlot()));
	/*
	UE_LOG(LogTemp, Warning, TEXT("threadrunning: %d"), threadrunning);

	Sleep(500);
	
	for (int a=0;;a++) {
		//UE_LOG(LogTemp, Warning, TEXT("dalsia iteracie"));
		if (threadrunning == false) {
			vypishodnot();
			UE_LOG(LogTemp, Warning, TEXT("tolkoto krat sa slucka otocila kym sa cakalo na finish simulacie: %d"), a);
			break;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("DA SA AJ TU DOSTAT? threadrunning: %d"), threadrunning);*/
	
	/*ngSpice_Command("bg_halt");
	UE_LOG(LogTemp, Warning, TEXT("pozastavene"));
	ngSpice_Command("alter c1=2");
    ngSpice_Command("listing");
	ngSpice_Command("bg_resume");*/

	/*FString curplot = ngSpice_CurPlot();
	UE_LOG(LogTemp, Warning, TEXT("\nCurrent plot is %s\n\n"), *curplot);*/
	

	// strana 354,,  ngSpice_AllVecs
	
	Super::BeginPlay();
	
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

bool wasrunning = false;
int ng_thread_runs(bool noruns, int ident, void* userdata)
{
	if (noruns) {
		UE_LOG(LogTemp, Warning, TEXT("bg not running\n"));

		if (wasrunning == true) {
			vypishodnot();
		}

		wasrunning = false;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("bg running\n"));
		wasrunning = true;
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

int ng_initdata(pvecinfoall intdata, int ident, void* userdata)
{
	/*FString name = intdata->name;
	UE_LOG(LogTemp, Warning, TEXT("Name of the plot: %s"), *(name));

	FString title = intdata->title;
	UE_LOG(LogTemp, Warning, TEXT("Title of the plot: %s"), *(title));

	FString date = intdata->date;
	UE_LOG(LogTemp, Warning, TEXT("Date of the plot: %s"), *(date));

	FString type = intdata->type;
	UE_LOG(LogTemp, Warning, TEXT("Type of the plot: %s\n"), *(type));*/

	vectorscount = intdata->veccount;
	for (int i = 0; i < vectorscount; i++) {
		/*UE_LOG(LogTemp, Warning, TEXT("Vector number: %d"), i);

		FString vecname = intdata->vecs[i]->vecname;
		UE_LOG(LogTemp, Warning, TEXT("Vector name: %s\n"), *(vecname));*/

		vectors[i] = (dvec*)intdata->vecs[i]->pdvec;

		/*FString vectorname = vector->v_name;
		UE_LOG(LogTemp, Warning, TEXT("Vector name: %s\n"), *(vectorname));

		double * vectorvalue = vector->v_realdata;

		for (int i = 0; i < vector->v_length; i++) {
			FString value = FString::SanitizeFloat(vectorvalue[i]);
			UE_LOG(LogTemp, Warning, TEXT("Vector value %d: %s\n"),i , *(value));
		}*/
	}

	return 0;
}

int ng_data(pvecvaluesall vdata, int numvecs, int ident, void* userdata)
{
	// tie init vektory su tam,, to nebudeme vytvarat, z initdata len zoberieme ukazatele a potom ich postupne zobrazime do logu,, napr tu rovno si mozem nejaku funkciu vytvorit ze plnenie 

	/*int i;
	for (i = 0; i < numvecs; i++) {
		//UE_LOG(LogTemp, Warning, TEXT("tu sa vektor vypisuje data"));
		FString name = vdata->vecsa[i]->name;
		FString value = FString::SanitizeFloat(vdata->vecsa[i]->creal); 
		UE_LOG(LogTemp, Warning, TEXT("Vector: %s a jeho hodnota: %s\n"), *(name), *(value));
	}*/

	return 0;
}
