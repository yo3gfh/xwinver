## XWINVER, windows version detector :-)

Copyright (c) 2020-2021 Adrian Petrila, YO3GFH<br>
    
Console app to detect windows version. Pretty silly but it gets the
job done (for me, at least). Built with Pelle's C compiler system.

---------
                       
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

---------

**Features**

* xwinver.exe returns a code according to OS version, so that
one can use it in batch files. See below for possible
return values. It uses Netxxx api from lm.h, since the stuff
from versionhelpers.h seems not to be reliable anymore.

**Building**

* I would leave it 32 bit, so that it can run on any old banger :-)
* Console subsystem version should be 5.0 so that it can be run 
from win2k and up. If you make it 4.0, it would prolly run on 
NT also, but I couldn't test.

**Return Values**

* 1100 - Win Server 2016
* 1063 - Win Server 2012 R2
* 1062 - Win Server 2012 
* 1061 - Win Server 2008 R2
* 1060 - Win Server 2008
* 1052 - Win Server 2003 R2
* 1050 - Win 2k Server
* 1040 - Possibly NT :-)
---------
* 100 - Win 10
* 63 - Win 8.1
* 62 - Win 8.0
* 61 - Win 7
* 60 - Win Vista
* 52 - Win XP x64
* 51 - Win XP
* 50 - Win 2k
* 40 - Possibly NT :-)

