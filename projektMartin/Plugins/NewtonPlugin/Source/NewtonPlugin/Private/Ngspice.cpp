// Martin Gulis & Tomas Liscak

#include "CoreMinimal.h"

#include "Ngspice.h"
#include "Circuit.h"


using namespace std;

NgSpice::NgSpice()
{
}

NgSpice &NgSpice::getInstance()
{
	static NgSpice instance;
	return instance;
}

bool NgSpice::AddCircuit(ACircuit *circuit)
{
	if (!m_circuit) {
		m_circuit = circuit;
		return true;
	}
	return false;
}

ACircuit *NgSpice::GetCircuit()
{
	return m_circuit;
}

int NgSpice::Init()
{
	m_circuit = NULL;
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

	/*if (m_circuit) {
		if (vi) {
			m_circuit->Report("GetVecInfo:");
			m_circuit->Report("V_name: " + FString(vi->v_name));
			m_circuit->Report("V_type: " + FString::FromInt(vi->v_type));
			m_circuit->Report("V_flags: " + FString::FromInt(vi->v_flags));
			m_circuit->Report("V_length: " + FString::FromInt(vi->v_length));
			for (int i = 0; i < vi->v_length; i++) {
				m_circuit->Report("V_realdata " + FString::FromInt(i) + ": Value: " + FString::SanitizeFloat(vi->v_realdata[i]));*/
				/*reporter->Report("V_compdata " + FString::FromInt(i) +
				": Cx_real: " + FString::SanitizeFloat(vi->v_compdata[i].cx_real) +
				" Cx_imag: " + FString::SanitizeFloat(vi->v_compdata[i].cx_imag));*/ // Crashes otherwise
			/*}
			m_circuit->Report(" ");
		}
		else {
			m_circuit->Report("GetVecInfo: NULL");
		}
	}*/
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

int NgSpice::cbSendChar(char *data, int id, void *user)
{
	NgSpice *ngspice = reinterpret_cast<NgSpice*>(user);
	/*if (ngspice && ngspice->m_circuit) {
		ngspice->m_circuit->Report("CbSendChar: " + FString(data) +
			" Id: " + FString::FromInt(id));
	}*/

	// Successful simulation
	/*if (FString(data).Contains("stdout No. of Data Rows : ", ESearchCase::IgnoreCase)) {
		if (ngspice->m_circuit) {
			ngspice->m_circuit->Report("cbSendChar: Simulation completed");
		}
	}*/
	// Unsuccessful simulation
	if(FString(data).StartsWith("stderr", ESearchCase::IgnoreCase)) {
		if (FString(data).Contains("stderr Warning: singular matrix:  check nodes ", ESearchCase::IgnoreCase)) {
			if (ngspice->m_circuit) {
				FString str(data);
				str.RemoveFromStart("stderr Warning: singular matrix:  check nodes ");
				ngspice->m_circuit->FillError(str.Left(str.Find(" ")));
			}
		}
		/*if (FString(data).Contains("stderr run simulation(s) aborted", ESearchCase::IgnoreCase)) {
			if (ngspice->m_circuit) {
				ngspice->m_circuit->Report("cbSendChar: Simulation exited with error");
			}
		}*/
	}

    return 0;
}

int NgSpice::cbSendStat(char *data, int id, void *user)
{
	NgSpice *ngspice = reinterpret_cast<NgSpice*>(user);
	/*if (ngspice->m_circuit) {
		ngspice->m_circuit->Report("CbSendStat: " + FString(data) +
			" Id: " + FString::FromInt(id));
	}*/
    return 0;
}

int NgSpice::cbControlledExit(int status, bool immediate, bool exit_upon_quit, int id, void *user)
{
	NgSpice *ngspice = reinterpret_cast<NgSpice*>(user);
	/*if (ngspice->m_circuit) {
		ngspice->m_circuit->Report("Status: " + FString::FromInt(status) +
			" Immediate: " + FString::FromInt(immediate) +
			" Exit_upon_quit: " + FString::FromInt(exit_upon_quit) +
			" Id: " + FString::FromInt(id));
	}*/
	return 0;
}

int NgSpice::cbSendData(pvecvaluesall data, int num, int id, void *user)
{
	NgSpice *ngspice = reinterpret_cast<NgSpice*>(user);

	if (ngspice->m_circuit) {
		ngspice->m_circuit->FillResults(data);
	}

	/*if (ngspice->m_circuit) {
		ngspice->m_circuit->Report("CbSendData:");
		ngspice->m_circuit->Report("Num: " + FString::FromInt(num));
		ngspice->m_circuit->Report("Veccount: " + FString::FromInt(data->veccount));
		ngspice->m_circuit->Report("Vecindex: " + FString::FromInt(data->vecindex));
		for (int i = 0; i < data->veccount; i++) {
			ngspice->m_circuit->Report("Vecvalues " + FString::FromInt(i) + ": Name: " + FString(data->vecsa[i]->name));
			ngspice->m_circuit->Report("Vecvalues " + FString::FromInt(i) + ": Creal: " + FString::SanitizeFloat(data->vecsa[i]->creal));*/
			/*ngspice->m_reporter->Report("Vecvalues " + FString::FromInt(i) + ": Cimag: " + FString::SanitizeFloat(data->vecsa[i]->cimag));
			ngspice->m_reporter->Report("Vecvalues " + FString::FromInt(i) + ": Is_scale: " + FString(data->vecsa[i]->is_scale ? "true" : "false"));
			ngspice->m_reporter->Report("Vecvalues " + FString::FromInt(i) + ": Is_complex: " + FString(data->vecsa[i]->is_complex ? "true" : "false"));*/
		/*}
		ngspice->m_circuit->Report("Id: " + FString::FromInt(id));
		ngspice->m_circuit->Report(" ");
	}*/
	return 0;
}

int NgSpice::cbSendInitData(pvecinfoall data, int id, void *user)
{
	NgSpice *ngspice = reinterpret_cast<NgSpice*>(user);
	/*if (ngspice->m_circuit) {
		ngspice->m_circuit->Report("CbSendInitData:");
		ngspice->m_circuit->Report("Name: " + FString(data->name));
		ngspice->m_circuit->Report("Title: " + FString(data->title));
		ngspice->m_circuit->Report("Date: " + FString(data->date));
		ngspice->m_circuit->Report("Type: " + FString(data->type));
		ngspice->m_circuit->Report("Veccount: " + FString::FromInt(data->veccount));
		for (int i = 0; i < data->veccount; i++) {
			ngspice->m_circuit->Report("VecInfo " + FString::FromInt(i) + ": Number: " + FString::FromInt(data->vecs[i]->number));
			ngspice->m_circuit->Report("VecInfo " + FString::FromInt(i) + ": Vecname: " + FString(data->vecs[i]->vecname));
			ngspice->m_circuit->Report("VecInfo " + FString::FromInt(i) + ": Is_real: " + FString(data->vecs[i]->is_real ? "true" : "false"));
		}
		ngspice->m_circuit->Report("Id: " + FString::FromInt(id));
		ngspice->m_circuit->Report(" ");
	}*/
	return 0;
}

int NgSpice::cbBGThreadRunning(bool is_running, int id, void *user)
{
	NgSpice *ngspice = reinterpret_cast<NgSpice*>(user);
	/*if (ngspice->m_circuit) {
		ngspice->m_circuit->Report("IsRunning: " + FString(is_running ? "true" : "false") +
			" Id: " + FString::FromInt(id));
	}*/

	// Simulation ends
	if (is_running) {
		ngspice->Command("destroy");
		//ngspice->Command("remcirc");
		ngspice->m_circuit = NULL;
	}

    return 0;
}
