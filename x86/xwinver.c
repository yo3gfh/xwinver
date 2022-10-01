/*
    XWINVER, windows version detector :-)
    ------------------------------------------------
    Copyright (c) 2020-2021 Adrian Petrila, YO3GFH
    
    Console app to detect windows version. Pretty silly but it gets the
    job done (for me, at least). Built with Pelle's C compiler system.

                                * * *
                                
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                * * *
    Features
    ---------
        - xwinver.exe returns a code according to OS version, so that
          one can use it in batch files. See the code below for possible
          return values. It uses Netxxx api from lm.h, since the stuff
          from versionhelpers.h seems not to be reliable anymore.

    Building
    ---------
        - I would leave it 32 bit, so that it can run on any old banger :-)
        - Console subsystem version should be 5.0 so that it can be run 
          from win2k and up. If you make it 4.0, it would prolly run on 
          NT also, but I couldn't test.
*/

#define UNICODE
#ifdef UNICODE
    #define _UNICODE
#endif
//#define DEBUG
#include <windows.h>
#include <lm.h>
#include <tchar.h>
#include <stdio.h>

int _tmain ( int argc, _TCHAR ** argv )
{
    LPSERVER_INFO_101   pSvi;
    NET_API_STATUS      nStatus;
    DWORD               dwMinor, dwMajor;
    int                 rVal;
    BOOL                isServer;

    _ftprintf (stderr,  TEXT("\nxWinVer v1.0 - copyright (c) 2020-2021") 
                        TEXT(" Adrian Petrila, YO3GFH\n\n")
                        TEXT("This program returns a value that you")
                        TEXT(" can use in batch files to identify what\n")
                        TEXT("OS you're on. Possible values are:\n")
                        TEXT("\t 100/1100 >= WIN 10/Srv 2016\n")
                        TEXT("\t  63/1063 >= WIN 8.1/Srv 2012 R2\n")
                        TEXT("\t  62/1062 >= WIN 8.0/Srv 2012\n")
                        TEXT("\t  61/1061 >= WIN 7/Srv 2008 R2\n")
                        TEXT("\t  60/1060 >= WIN Vista/Srv 2008\n")
                        TEXT("\t  52/1052 >= WIN XP x64/Srv 2003 R2\n")
                        TEXT("\t  51/1051 >= WIN XP/?\n")
                        TEXT("\t  50/1050 >= WIN 2k\n")
                        TEXT("\t  40/1040 >= Antique :-)\n\n"));

    pSvi                = NULL;
    rVal                = 0;
    dwMinor             = 0;
    dwMajor             = 0;
    isServer            = FALSE;

    nStatus = NetServerGetInfo ( NULL, 101, (LPBYTE *)&pSvi );

    if ( nStatus == NERR_Success )
    {
    #ifdef DEBUG
        _ftprintf ( stderr, TEXT("Success!\n") );
        _ftprintf ( stdout, TEXT("Platform ID: %u\n"), 
            pSvi->sv101_platform_id );
        _ftprintf ( stdout, TEXT("Major Ver: %u\n"), 
            pSvi->sv101_version_major & MAJOR_VERSION_MASK );
        _ftprintf ( stdout, TEXT("Minor Ver: %u\n"), 
            pSvi->sv101_version_minor );
    #endif
        dwMajor = pSvi->sv101_version_major & MAJOR_VERSION_MASK;
        dwMinor = pSvi->sv101_version_minor;

        // see if we have the server version, since
        // major.minor are the same for both types
        if ( (pSvi->sv101_type & SV_TYPE_DOMAIN_CTRL) ||
             (pSvi->sv101_type & SV_TYPE_DOMAIN_BAKCTRL) ||
             (pSvi->sv101_type & SV_TYPE_SERVER_NT) )
                isServer = TRUE;

        rVal = (dwMajor * 10) + dwMinor;
    }
    else
    {
        _ftprintf ( stderr, TEXT("Cannot execute NetServerGetInfo, ") 
                            TEXT("GetLastError returned: %u\n"), 
                    GetLastError());
    }

    if ( pSvi != NULL )
        NetApiBufferFree ( pSvi );

    // make it so we can differentiate between client
    // and server versions
    if ( isServer )
        rVal += 1000;

    _ftprintf ( stdout, TEXT("\n%d\n"), rVal );
    #ifdef DEBUG
        getchar();
    #endif
    return rVal;
}
