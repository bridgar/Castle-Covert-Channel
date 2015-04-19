;	Castle is a covert channel for use with 0 A.D.
;   Copyright (C) 2015  Bridger Hahn
;
;   This program is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 3 of the License, or
;   (at your option) any later version.
;
;   This program is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License
;   along with this program.  If not, see <http://www.gnu.org/licenses/>.


WinWait, 0 A.D., 
IfWinNotActive, 0 A.D., , WinActivate, 0 A.D., 
WinWaitActive, 0 A.D., 
MouseClick, left,  998,  577
Sleep, 100
MouseClick, left,  265,  263
Sleep, 100
MouseClick, left,  423,  261
Sleep, 100
MouseClick, left,  988,  419
Sleep, 100
Send, {SHIFTDOWN}{HOME}{SHIFTUP}{BACKSPACE}
Sleep, 100
Send, %1%
Sleep, 100
MouseClick, left,  899,  498
Sleep, 1000