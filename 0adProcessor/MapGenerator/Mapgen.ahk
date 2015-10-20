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


;params are as follows:
;1 x-pixel start
;2 y-pixel start
;3 x-pixel offset
;4 y-pixel offset
;5 x-column count
;6 y-row count
;7 x-pixel minimap player 1
;8 y-pixel minimap player 1
;9 x-pixel minimap player 2
;10 y-pixel minimap player 2


MsgBox,,Mapgen,Please open the map editor with the designated settings,

;WinWait, 0 A.D.,
;IfWinNotActive, 0 A.D., , WinActivate, 0 A.D., 
;WinWaitActive, 0 A.D., 


MsgBox,,Mapgen,Select the designated unit for player 1 to be placed then press OK to continue,

;click on the designated minimap location for player 1
Click %7%, %8%

col_ind = 0

;column loop
Loop, %5%
	{
		row_ind = 0
		;row loop		
		Loop, %6%
			{
				;pressing escape exits the script
				if GetKeyState("Esc")
					{
						ExitApp
					}
				
				;xpixel equals x-pixel start + col_ind * offset
				x_pixel = %1%
				x_off = %3%
				x_pixel := x_pixel + col_ind * x_off
				
				;ypixel equals y-pixel start + row_ind * offset
				y_pixel = %2%
				y_off = %4%
				y_pixel := y_pixel + row_ind * y_off
				
				Click  %x_pixel%, %y_pixel%

				row_ind := row_ind + 1
			}
			
			col_ind := col_ind + 1
	}

MsgBox,,Mapgen,Select the designated unit for player 2 to be placed then press OK to continue,

;click on the designated minimap location for player 2
Click %9%, %10%
	
col_ind = 0

;column loop
Loop, %5%
	{
		row_ind = 0
		;row loop		
		Loop, %6%
			{
				;pressing escape exits the script
				if GetKeyState("Esc")
					{
						ExitApp
					}
				
				;xpixel equals x-pixel start + col_ind * offset
				x_pixel = %1%
				x_off = %3%
				x_pixel := x_pixel + col_ind * x_off
				
				;ypixel equals y-pixel start + row_ind * offset
				y_pixel = %2%
				y_off = %4%
				y_pixel := y_pixel + row_ind * y_off
				
				Click  %x_pixel%, %y_pixel%
				
				row_ind := row_ind + 1
			}
			
			col_ind := col_ind + 1
	}
