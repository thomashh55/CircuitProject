/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2016 CERN
 * @author Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
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

#include "sharedspice.h"
#include "Reporter.h"

using namespace std;

class NGSPICE {

public:
    NGSPICE();
    virtual ~NGSPICE();

	void SetReporter(AReporter *reporter);

    int Init();
	int Command(char *cmd);
	void GetVecInfo(char *vecname);
	int LoadCirc(char **circarray);
	char *GetPlotName();
	char **GetAllPlots();
	char **GetAllVecs(char* plotname);
	bool IsRunning();
	bool SetBreakpoint(double time);

private:
    static int cbSendChar(char *what, int id, void *user);
    static int cbSendStat(char *what, int id, void *user);
	static int cbControlledExit(int status, bool immediate, bool exit_upon_quit, int id, void *user);
	static int cbSendData(pvecvaluesall what, int num, int id, void *user);
	static int cbSendInitData(pvecinfoall what, int id, void *user);
    static int cbBGThreadRunning(bool is_running, int id, void *user);

	AReporter* m_reporter;
};
