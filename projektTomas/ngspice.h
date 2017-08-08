// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ngspice/sharedspice.h"
#include "ngspice/dvec.h"
#include <signal.h>
#include <windows.h>

class ACircuit;

class NgSpice {

public:
	// Returns singleton instance
	static NgSpice &getInstance();
	static dvec ** vectors;
	static int vectorscount;

	// Vectors returned from simulation
	//static dvec ** resultVectors; // neviem preco toto mi tu nejde spravit
	//static int resultVectorsCount;

	// Adds circuit for returned values
	virtual int AddCircuit(ACircuit *circuit);
	virtual void RemoveCircuit(ACircuit *circuit);

	// Callback function for results
	void setCallbackForResults(int indexToCircuitArray);

	// NgSpice commands
	virtual int Init();
	virtual int Command(char *cmd);
	virtual pvector_info GetVecInfo(char *vecname);
	virtual int LoadCirc(char **circarray);
	virtual char *GetPlotName();
	virtual char **GetAllPlots();
	virtual char **GetAllVecs(char* plotname);
	virtual bool IsRunning();
	virtual bool SetBreakpoint(double time);

private:
	NgSpice();
	NgSpice(NgSpice const&);
	void operator=(NgSpice const&);

	// NgSpice callback functions
	static int cbSendChar(char *what, int id, void *user);
	static int cbSendStat(char *what, int id, void *user);
	static int cbControlledExit(int status, bool immediate, bool exit_upon_quit, int id, void *user);
	static int cbSendData(pvecvaluesall what, int num, int id, void *user);
	static int cbSendInitData(pvecinfoall what, int id, void *user);
	static int cbBGThreadRunning(bool is_running, int id, void *user);

	TArray<ACircuit*> m_circuitArray;

};