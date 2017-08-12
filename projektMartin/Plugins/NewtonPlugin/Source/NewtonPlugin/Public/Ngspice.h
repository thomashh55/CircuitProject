// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "sharedspice.h"

#include "CoreMinimal.h"

class ACircuit;

class NEWTONPLUGIN_API NgSpice {

public:
	// Returns singleton instance
	static NgSpice &getInstance();

	// Adds circuit
	virtual bool AddCircuit(ACircuit *circuit);
	virtual ACircuit *GetCircuit();

	// NgSpice commands
	virtual int Init();
	virtual int Command(char *cmd);
	virtual pvector_info GetVecInfo(char *vecname);
	virtual int LoadCirc(char **circarray);
	virtual char *GetPlotName();
	virtual char **GetAllPlots();
	virtual char **GetAllVecs(char *plotname);
	virtual bool IsRunning();
	virtual bool SetBreakpoint(double time);

private:
	NgSpice();
	NgSpice(NgSpice const&);
	void operator=(NgSpice const&);

	// NgSpice callback functions
    static int cbSendChar(char *data, int id, void *user);
    static int cbSendStat(char *data, int id, void *user);
	static int cbControlledExit(int status, bool immediate, bool exit_upon_quit, int id, void *user);
	static int cbSendData(pvecvaluesall data, int num, int id, void *user);
	static int cbSendInitData(pvecinfoall data, int id, void *user);
    static int cbBGThreadRunning(bool is_running, int id, void *user);

	ACircuit *m_circuit;

};
