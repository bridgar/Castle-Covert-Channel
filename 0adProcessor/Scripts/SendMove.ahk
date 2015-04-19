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


;click as fast as possible and have max computing time equal to min computing time
setMousedelay -1
setbatchlines -1

WinWait, 0 A.D.,
IfWinNotActive, 0 A.D., , WinActivate, 0 A.D., 
WinWaitActive, 0 A.D., 

ST := A_TickCount

Send, {Escape}
Send, {ShiftDown}
Loop, 200
	{
	
	if GetKeyState("Esc")
		{
		Send, {ShiftUp}
		Sleep, 10000
		Exit
		}
	
	xInd := (A_Index * 2 - 1)
	zInd := (A_Index * 2)
	
	xInd := %xInd%
	zInd := %zInd%
	
	if(xInd = 0)
	{
		Continue
	}
	
	Click %xInd%, %zInd%
	;Sleep, 1
	}
Send, {ShiftUp}

;Sleep, 1000

Click right, %401%, %402%

ET := A_TickCount - ST
;MsgBox %Clicks_Second% clicks per second.`n%Count% clicks total.`n%ET% MS total.