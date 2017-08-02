// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Ngspice.h"

using namespace std;

NgSpice::NgSpice()
{
	Init();
}

NgSpice& NgSpice::getInstance()
{
	static NgSpice instance;
	return instance;
}

void NgSpice::SetReporter(AReporter *reporter)
{
	m_reporter = reporter;
	m_reporter->Report("Reporter set");
}

int NgSpice::Init()
{
	int ret = ngSpice_Init(&cbSendChar, &cbSendStat, &cbControlledExit, &cbSendData, &cbSendInitData, &cbBGThreadRunning, this);
	return ret;
}

int NgSpice::Command(char *cmd)
{
	int ret = ngSpice_Command(cmd);
	return ret;
}

pvector_info NgSpice::GetVecInfo(char *vecname)
{
	pvector_info vi = ngGet_Vec_Info(vecname);
	if (m_reporter != NULL) {
		if (vi) {
			m_reporter->Report("GetVecInfo:");
			m_reporter->Report("V_name: " + FString(vi->v_name));
			m_reporter->Report("V_type: " + FString::FromInt(vi->v_type));
			m_reporter->Report("V_flags: " + FString::FromInt(vi->v_flags));
			m_reporter->Report("V_length: " + FString::FromInt(vi->v_length));
			for (int i = 0; i < vi->v_length; i++) {
				m_reporter->Report("V_realdata " + FString::FromInt(i) + ": Value: " + FString::SanitizeFloat(vi->v_realdata[i]));
				/*reporter->Report("V_compdata " + FString::FromInt(i) +
				": Cx_real: " + FString::SanitizeFloat(vi->v_compdata[i].cx_real) +
				" Cx_imag: " + FString::SanitizeFloat(vi->v_compdata[i].cx_imag));*/ // Crashes otherwise
			}
			m_reporter->Report(" ");
		}
		else {
			m_reporter->Report("GetVecInfo: NULL");
		}
	}
	return vi;
}

int NgSpice::LoadCirc(char **circarray)
{
	int ret = ngSpice_Circ(circarray);
	return ret;
}

char *NgSpice::GetPlotName()
{
	char *name = ngSpice_CurPlot();
	return name;
}

char **NgSpice::GetAllPlots()
{
	char **plots = ngSpice_AllPlots();
	return plots;
}

char **NgSpice::GetAllVecs(char* plotname)
{
	char **vecs = ngSpice_AllVecs(plotname);
	return vecs;
}

bool NgSpice::IsRunning()
{
	bool bIsRunning = ngSpice_running();
	return bIsRunning;
}

bool NgSpice::SetBreakpoint(double time)
{
	bool bIsSet = ngSpice_SetBkpt(time);
	return bIsSet;
}

int NgSpice::cbSendChar(char *what, int id, void *user)
{
	NgSpice* ngspice = reinterpret_cast<NgSpice*>(user);
	if (ngspice->m_reporter != NULL) {
		ngspice->m_reporter->Report("CbSendChar: " + FString(what) +
			" Id: " + FString::FromInt(id));
	}
    return 0;
}

int NgSpice::cbSendStat(char *what, int id, void *user)
{
	NgSpice* ngspice = reinterpret_cast<NgSpice*>(user);
	if (ngspice->m_reporter != NULL) {
		ngspice->m_reporter->Report("CbSendStat: " + FString(what) +
			" Id: " + FString::FromInt(id));
	}
    return 0;
}

int NgSpice::cbControlledExit(int status, bool immediate, bool exit_upon_quit, int id, void *user)
{
	NgSpice* ngspice = reinterpret_cast<NgSpice*>(user);
	if (ngspice->m_reporter != NULL) {
		ngspice->m_reporter->Report("Status: " + FString::FromInt(status) +
			" Immediate: " + FString::FromInt(immediate) +
			" Exit_upon_quit: " + FString::FromInt(exit_upon_quit) +
			" Id: " + FString::FromInt(id));
	}
	return 0;
}

int NgSpice::cbSendData(pvecvaluesall what, int num, int id, void *user)
{
	NgSpice* ngspice = reinterpret_cast<NgSpice*>(user);
	if (ngspice->m_reporter != NULL) {
		ngspice->m_reporter->Report("CbSendData:");
		ngspice->m_reporter->Report("Veccount: " + FString::FromInt(what->veccount));
		ngspice->m_reporter->Report("Vecindex: " + FString::FromInt(what->vecindex));
		for (int i = 0; i < what->veccount; i++) {
			ngspice->m_reporter->Report("Vecvalues " + FString::FromInt(i) + ": Name: " + FString(what->vecsa[i]->name));
			ngspice->m_reporter->Report("Vecvalues " + FString::FromInt(i) + ": Creal: " + FString::SanitizeFloat(what->vecsa[i]->creal));
			/*ngspice->m_reporter->Report("Vecvalues " + FString::FromInt(i) + ": Cimag: " + FString::SanitizeFloat(what->vecsa[i]->cimag));
			ngspice->m_reporter->Report("Vecvalues " + FString::FromInt(i) + ": Is_scale: " + FString(what->vecsa[i]->is_scale ? "true" : "false"));
			ngspice->m_reporter->Report("Vecvalues " + FString::FromInt(i) + ": Is_complex: " + FString(what->vecsa[i]->is_complex ? "true" : "false"));*/
		}
		ngspice->m_reporter->Report("Id: " + FString::FromInt(id));
		ngspice->m_reporter->Report(" ");
	}
	return 0;
}

int NgSpice::cbSendInitData(pvecinfoall what, int id, void *user)
{
	NgSpice* ngspice = reinterpret_cast<NgSpice*>(user);
	if (ngspice->m_reporter != NULL) {
		ngspice->m_reporter->Report("CbSendInitData:");
		ngspice->m_reporter->Report("Name: " + FString(what->name));
		ngspice->m_reporter->Report("Title: " + FString(what->title));
		ngspice->m_reporter->Report("Date: " + FString(what->date));
		ngspice->m_reporter->Report("Type: " + FString(what->type));
		ngspice->m_reporter->Report("Veccount: " + FString::FromInt(what->veccount));
		for (int i = 0; i < what->veccount; i++) {
			ngspice->m_reporter->Report("VecInfo " + FString::FromInt(i) + ": Number: " + FString::FromInt(what->vecs[i]->number));
			ngspice->m_reporter->Report("VecInfo " + FString::FromInt(i) + ": Vecname: " + FString(what->vecs[i]->vecname));
			ngspice->m_reporter->Report("VecInfo " + FString::FromInt(i) + ": Is_real: " + FString(what->vecs[i]->is_real ? "true" : "false"));
		}
		ngspice->m_reporter->Report("Id: " + FString::FromInt(id));
		ngspice->m_reporter->Report(" ");
	}
	return 0;
}

int NgSpice::cbBGThreadRunning(bool is_running, int id, void *user)
{
	NgSpice* ngspice = reinterpret_cast<NgSpice*>(user);
	if (ngspice->m_reporter != NULL) {
		ngspice->m_reporter->Report("IsRunning: " + FString(is_running ? "true" : "false") +
			" Id: " + FString::FromInt(id));
	}
    return 0;
}
