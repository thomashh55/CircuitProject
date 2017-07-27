/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2016 CERN
 * @author Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
 * @author Maciej Suminski <maciej.suminski@cern.ch>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * https://www.gnu.org/licenses/gpl-3.0.html
 * or you may search the http://www.gnu.org website for the version 3 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "NewtonProject.h"
#include "ngspice.h"

#include <sstream>
#include <stdexcept>

#include <algorithm>

using namespace std;

NGSPICE::NGSPICE()
{
}


NGSPICE::~NGSPICE()
{
}


int NGSPICE::Init()
{
    setlocale( LC_ALL, "C" );
	int iret = ngSpice_Init(&cbSendChar, &cbSendStat, &cbControlledExit, &cbSendData, &cbSendInitData, &cbBGThreadRunning, this);
    setlocale( LC_ALL, "" );
	return iret;
}


int NGSPICE::Command(char *cmd)
{
	setlocale(LC_ALL, "C");
	int iret = ngSpice_Command(cmd);
	setlocale(LC_ALL, "");
	return iret;
}


void NGSPICE::GetVecInfo(char *vecname)
{
	setlocale(LC_ALL, "C");
	pvector_info vi = ngGet_Vec_Info(vecname);
	setlocale(LC_ALL, "");

	/*if (vi) {
		int length = vi->v_length;

		if (vi->v_realdata)
		{
			for (int i = 0; i < length; i++)
			{
				data.push_back(vi->v_realdata[i]);
			}
		}
		else if (vi->v_compdata)
		{
			for (int i = 0; i < length; i++)
			{
				assert(vi->v_compdata[i].cx_imag == 0.0);
				data.push_back(vi->v_compdata[i].cx_real);
			}
		}
	}*/
}


int NGSPICE::LoadCirc(char **circarray)
{
	setlocale(LC_ALL, "C");
	int iret = ngSpice_Circ(circarray);
	setlocale(LC_ALL, "");
	return iret;
}


char *NGSPICE::GetPlotName()
{
	setlocale(LC_ALL, "C");
	char *name = ngSpice_CurPlot();
	setlocale(LC_ALL, "");
	return name;
}


char **NGSPICE::GetAllPlots()
{
	setlocale(LC_ALL, "C");
	char **plots = ngSpice_AllPlots();
	setlocale(LC_ALL, "");
	return plots;
}


char **NGSPICE::GetAllVecs(char* plotname)
{
	setlocale(LC_ALL, "C");
	char **vecs = ngSpice_AllVecs(plotname);
	setlocale(LC_ALL, "");
	return vecs;
}


bool NGSPICE::IsRunning()
{
	setlocale(LC_ALL, "C");
	bool bIsRunning = ngSpice_running();
	setlocale(LC_ALL, "");
	return bIsRunning;
}


int NGSPICE::cbSendChar(char *what, int id, void *user)
{
    NGSPICE* ngspice = reinterpret_cast<NGSPICE*>(user);
	ngspice->reporter->Report("CbSendChar: " + FString(what) +
		" Id: " + FString::FromInt(id));
    return 0;
}


int NGSPICE::cbSendStat(char *what, int id, void *user)
{
    NGSPICE* ngspice = reinterpret_cast<NGSPICE*>(user);
	ngspice->reporter->Report("CbSendStat: " + FString(what) +
		" Id: " + FString::FromInt(id));
    return 0;
}


int NGSPICE::cbControlledExit(int status, bool immediate, bool exit_upon_quit, int id, void *user)
{
	NGSPICE* ngspice = reinterpret_cast<NGSPICE*>(user);
	ngspice->reporter->Report("Status: " + FString::FromInt(status) +
		" Immediate: " + FString::FromInt(immediate) +
		" Exit_upon_quit: " + FString::FromInt(exit_upon_quit) +
		" Id: " + FString::FromInt(id));
	return 0;
}


int NGSPICE::cbSendData(pvecvaluesall what, int num, int id, void *user)
{
	NGSPICE* ngspice = reinterpret_cast<NGSPICE*>(user);
	ngspice->reporter->Report("cbSendData:");
	ngspice->reporter->Report("Veccount: " + FString::FromInt(what->veccount));
	ngspice->reporter->Report("Vecindex: " + FString::FromInt(what->vecindex));
	for (int i = 0; i < what->veccount; i++) {
		ngspice->reporter->Report("Vecvalues " + FString::FromInt(i) + ": Name: " + FString(what->vecsa[i]->name));
		ngspice->reporter->Report("Vecvalues " + FString::FromInt(i) + ": Creal: " + FString::SanitizeFloat(what->vecsa[i]->creal));
		ngspice->reporter->Report("Vecvalues " + FString::FromInt(i) + ": Cimag: " + FString::SanitizeFloat(what->vecsa[i]->cimag));
		ngspice->reporter->Report("Vecvalues " + FString::FromInt(i) + ": Is_scale: " + FString(what->vecsa[i]->is_scale ? "true" : "false"));
		ngspice->reporter->Report("Vecvalues " + FString::FromInt(i) + ": Is_complex: " + FString(what->vecsa[i]->is_complex ? "true" : "false"));
	}
	ngspice->reporter->Report("Id: " + FString::FromInt(id));
	ngspice->reporter->Report(" ");
	return 0;
}


int NGSPICE::cbSendInitData(pvecinfoall what, int id, void *user)
{
	NGSPICE* ngspice = reinterpret_cast<NGSPICE*>(user);
	ngspice->reporter->Report("CbSendInitData:");
	ngspice->reporter->Report("Name: " + FString(what->name));
	ngspice->reporter->Report("Title: " + FString(what->title));
	ngspice->reporter->Report("Date: " + FString(what->date));
	ngspice->reporter->Report("Type: " + FString(what->type));
	ngspice->reporter->Report("Veccount: " + FString::FromInt(what->veccount));
	for (int i = 0; i < what->veccount; i++) {
		ngspice->reporter->Report("VecInfo " + FString::FromInt(i) + ": Number: " + FString::FromInt(what->vecs[i]->number));
		ngspice->reporter->Report("VecInfo " + FString::FromInt(i) + ": Vecname: " + FString(what->vecs[i]->vecname));
		ngspice->reporter->Report("VecInfo " + FString::FromInt(i) + ": Is_real: " + FString(what->vecs[i]->is_real ? "true" : "false"));
	}
	ngspice->reporter->Report("Id: " + FString::FromInt(id));
	ngspice->reporter->Report(" ");
	return 0;
}


int NGSPICE::cbBGThreadRunning( bool is_running, int id, void* user )
{
    NGSPICE* ngspice = reinterpret_cast<NGSPICE*>(user);
	ngspice->reporter->Report("IsRunning: " + FString(is_running ? "true" : "false") +
		" Id: " + FString::FromInt(id));
    return 0;
}
