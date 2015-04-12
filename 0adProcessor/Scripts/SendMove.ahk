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