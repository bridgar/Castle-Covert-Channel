#	Castle is a covert channel for use with 0 A.D.
#    Copyright (C) 2015  Bridger Hahn
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#Generates a 0ad map with units spaced according to input constraints.
#inputs: x_start, z_start, x_max, z_max, x_space, z_space, template, orientation, seed, filename

import linecache
import sys
import time
import os

template = "structures/brit_outpost"
orientation = 1.57
seed = 1
filename = "Blank_Map.xml"


#Create output file with the settings preamble.
settings = open("settings.xml", 'r')
output = open(filename, 'w')

lines = settings.readlines()
for i in range(0, len(lines)):
    output.write(lines[i])

output.close()
settings.close()

#Append entities to output file.
uid = 40
output = open(filename, 'a')

x_start = 300
z_start = 200
x_max = 500
z_max = 456
x_space = 8
z_space = 8

for i in range(x_start, x_max, x_space):
    for j in range(z_max, z_start, -z_space):
        output.write("      <Entity uid=\""+str(uid)+"\">\n")
        output.write("          <Template>"+template+"</Template>\n")
        output.write("          <Player>1</Player>\n")
        output.write("          <Position x=\""+str(i)+"\" z=\""+str(j)+"\" />\n")
        output.write("          <Orientation y=\""+str(orientation)+"\"/>\n")
        output.write("          <Actor seed=\""+str(seed)+"\"/>\n")
        output.write("      </Entity>\n")
        uid = uid + 1
		
x_start = 600
z_start = 200
x_max = 800
z_max = 456
x_space = 8
z_space = 8
		
#for i in range(x_start, x_max, x_space):
#    for j in range(z_max, z_start, -z_space):
#        output.write("      <Entity uid=\""+str(uid)+"\">\n")
#        output.write("          <Template>"+template+"</Template>\n")
#        output.write("          <Player>1</Player>\n")
#        output.write("          <Position x=\""+str(i)+"\" z=\""+str(j)+"\" />\n")
#        output.write("          <Orientation y=\""+str(orientation)+"\"/>\n")
#        output.write("          <Actor seed=\""+str(seed)+"\"/>\n")
#        output.write("      </Entity>\n")
#        uid = uid + 1		
x_start = 300
z_start = 600
x_max = 500
z_max = 856
x_space = 8
z_space = 8

for i in range(x_start, x_max, x_space):
    for j in range(z_max, z_start, -z_space):
        output.write("      <Entity uid=\""+str(uid)+"\">\n")
        output.write("          <Template>"+template+"</Template>\n")
        output.write("          <Player>2</Player>\n")
        output.write("          <Position x=\""+str(i)+"\" z=\""+str(j)+"\" />\n")
        output.write("          <Orientation y=\""+str(orientation)+"\"/>\n")
        output.write("          <Actor seed=\""+str(seed)+"\"/>\n")
        output.write("      </Entity>\n")
        uid = uid + 1		

x_start = 600
z_start = 600
x_max = 800
z_max = 856
x_space = 8
z_space = 8
		
#for i in range(x_start, x_max, x_space):
#    for j in range(z_max, z_start, -z_space):
#        output.write("      <Entity uid=\""+str(uid)+"\">\n")
#        output.write("          <Template>"+template+"</Template>\n")
#        output.write("          <Player>2</Player>\n")
#        output.write("          <Position x=\""+str(i)+"\" z=\""+str(j)+"\" />\n")
#        output.write("          <Orientation y=\""+str(orientation)+"\"/>\n")
#        output.write("          <Actor seed=\""+str(seed)+"\"/>\n")
#        output.write("      </Entity>\n")
#        uid = uid + 1				
		
#Appending tail to output file
output.write("  </Entities>\n")
output.write(" <Paths/>\n")
output.write("</Scenario>\n")

output.close()

               
