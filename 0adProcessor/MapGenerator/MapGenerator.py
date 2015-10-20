#instructions format:
#game|resolution|map size|map type|unit|x-pixel start|y-pixel start|x-pixel offset|y-pixel offset|x-xolumn count|y-row count|x-pixel minimap player 1|y-pixel minimap player 1|x-pixel minimap player 2|y-pixel minimap player 2


from subprocess import call
import sys
import hashlib

#longest common substring
#dynamic programming
def lcs(s1, s2):
	m = [[0] * (1 + len(s2)) for i in range(1 + len(s1))]
	longest, x_longest = 0, 0
	for x in range(1, 1 + len(s1)):
		for y in range(1, 1 + len(s2)):
			if s1[x - 1] == s2[y - 1]:
				m[x][y] = m[x - 1][y - 1] + 1
				if m[x][y] > longest:
					longest = m[x][y]
					x_longest = x
			else:
				m[x][y] = 0
	return s1[x_longest - longest: x_longest]

#this will find the middle common substring of your five bins and return the header, body, and footer
def bin_slicer():
	print 'Remember the file extension for your map files and then rename them to 1.bin 2.bin 3.bin 4.bin and 5.bin'
	raw_input('Press enter when you are ready')
	#read files into memory
	with open('1.bin', 'rb') as f:
		one = f.read()
	with open('2.bin', 'rb') as f:
		two = f.read()
	with open('3.bin', 'rb') as f:
		three = f.read()
	with open('4.bin', 'rb') as f:
		four = f.read()
	with open('5.bin', 'rb') as f:
		five = f.read()
	
	
	#some assumptions are being made about the map files here
	#we are assuming that the bulk of the map file contents will be the same across the files
	#we are assuming that only a header and footer on the file will change due to changes in metadata
	#this series of lcs calls should find the substance of the file, which does not change between files
	temp = lcs(one,two)
	temp_2 = lcs(temp,three)
	temp_3 = lcs(temp_2,four)
	body = lcs(temp_3,five)
	
	#we will use one as our representative file, using its header and footer as the official header and footer
	start = one.find(body)
	end = start + len(body)
	header= one[0:start]
	footer = one[end:]
	
	return [header, body, footer]

#create map from the instructions file
def create_from_instructions():
	with open(INSTRUCTIONS, 'r') as f:
		ins = f.read()
		ins_s = ins.split('|')
		print 'Please launch ', ins_s[0], ' in ', ins_s[1], ' resolution and open the map editor.'
		print 'When selecting your unit in the map editor, please select ', ins_s[4]
		print 'The map size must be ', ins_s[2]
		print 'The map type must be ', ins_s[3]
		print 'You will need to create five versions of the same map, varying as many meta-data details as possible'
		print 'Over the five map creations, vary as many options in map creation as possible without changing any previously specified settings'
		print 'If possible, try to change your in-game name between map creations'
		raw_input('Press enter when you are ready')
		
		call(["Mapgen.exe",ins_s[5], ins_s[6], ins_s[7], ins_s[8], ins_s[9], ins_s[10], ins_s[11], ins_s[12], ins_s[13], ins_s[14]])
		
		raw_input('Please set up for another map creation, vary settings, and press enter when you are ready')
		
		call(["Mapgen.exe",ins_s[5], ins_s[6], ins_s[7], ins_s[8], ins_s[9], ins_s[10], ins_s[11], ins_s[12], ins_s[13], ins_s[14]])
		
		raw_input('Please set up for another map creation, vary settings, and press enter when you are ready')
		
		call(["Mapgen.exe",ins_s[5], ins_s[6], ins_s[7], ins_s[8], ins_s[9], ins_s[10], ins_s[11], ins_s[12], ins_s[13], ins_s[14]])
		
		raw_input('Please set up for another map creation, vary settings, and press enter when you are ready')
		
		call(["Mapgen.exe",ins_s[5], ins_s[6], ins_s[7], ins_s[8], ins_s[9], ins_s[10], ins_s[11], ins_s[12], ins_s[13], ins_s[14]])
		
		raw_input('Please set up for another map creation, vary settings, and press enter when you are ready')
		
		call(["Mapgen.exe",ins_s[5], ins_s[6], ins_s[7], ins_s[8], ins_s[9], ins_s[10], ins_s[11], ins_s[12], ins_s[13], ins_s[14]])
		
		print 'For the next step, please find the five map files on your computer and copy them to the same directory as this script'
	return
	
#modify a map file that was made from an instructions file
def modify_from_instructions():
	slices = bin_slicer()
	body = slices[1]
	
	#read the header and footer
	with open('header.bin', 'rb') as f:
		header = f.read()
	with open('footer.bin', 'rb') as f:
		footer = f.read()
	
	#put together the header, body, and footer
	with open('map.bin', 'wb') as f:
		f.write(header + body + footer)
	
	print 'Your map has been prepared and saved to map.bin'
	
	print 'The md5 sum of your map is being calculated and compared to the one provided to you'
	raw_input('Please keep sum.txt in the same directory as this script and press enter to continue')
	
	#calculate md5 sum
	m = hashlib.md5()
	m.update(header + body + footer)
	sum = m.digest()
	
	with open('sum.txt', 'r') as f:
		true_sum = f.read()
		if true_sum != sum:
			print 'Your md5 sum does not match the one provided to you. please try this process again'
			print 'If your md5 sum continuously does not match, try using another RTS game'
			return
	
	print 'Your md5 sum matches the provided md5 sum. Your map is correct'
	print 'You should change the extension of map.bin to the original extension of your map files and move it into your game\'s map directory'
	raw_input('You are finished')
	return
	
#create instructions for others to make a map
def create_instructions():
	with open (INSTRUCTIONS, 'w') as f:
		print 'Please name your RTS game'
		game = ''
		game = raw_input()
		print 'Please specify a resolution to run your game. Remember that others will have to run at the same resolution as you. Try not to exceed 1600x900'
		resolution = raw_input()
		print 'Please specify the size of the map'
		map_size = raw_input()
		print 'Please specify the map type. If there are several map type options, list them here'
		map_type = raw_input()
		print 'Please specify your unit for your grid. Be as specific as possible'
		unit = raw_input()
		print 'For the following pixel coordinates, please use the DetectClick.exe script to find the coordinates'
		print 'Please specify the x-pixel coordinate at the top left of your grid of units'
		x_start = raw_input()
		print 'Please specify the y-pixel coordinate at the top left of your grid of units'
		y_start = raw_input()
		print 'Please specify the x-pixel offset between units in your grid'
		x_offset = raw_input()
		print 'Please specify the y-pixel offset between units in your grid'
		y_offset = raw_input()
		print 'Please specify the number of columns in your grid of units'
		columns = raw_input()
		print 'Please specify the number of rows in your grid of units'
		rows = raw_input()
		print 'Please specify the x-pixel minimap coordinate for player 1'
		p1_x = raw_input()
		print 'Please specify the y-pixel minimap coordinate for player 1'
		p1_y = raw_input()
		print 'Please specify the x-pixel minimap coordinate for player 2'
		p2_x = raw_input()
		print 'Please specify the y-pixel minimap coordinate for player 2'
		p2_y = raw_input()
		
		f.write(game + DELIM + resolution + DELIM + map_size + DELIM + map_type + DELIM + unit + DELIM + x_start + DELIM + y_start + DELIM + x_offset + DELIM + y_offset + DELIM + columns + DELIM + rows + DELIM + p1_x + DELIM + p1_y + DELIM + p2_x + DELIM + p2_y)
	
	print 'Your instructions file has been saved to instructions.txt'
	print 'Send this to the person on the other end'
	return

#modify a map from instructions that you've made
def modify_instructions():
	slices = bin_slicer()
	header = slices[0]
	body = slices[1]
	footer = slices[2]
	
	#write the header, footer, and full map
	with open('header.bin', 'wb') as f:
		f.write(header)
	with open('footer.bin', 'wb') as f:
		f.write(footer)
	with open('map.bin', 'wb') as f:
		f.write(header + body + footer)
		
		
	print 'Your map has been prepared and saved to map.bin'
	print 'You should change the extension of map.bin to the original extension of your map files and move it into your game\'s map directory'
	print 'Do not change the extension for header.bin or footer.bin'
	print 'Send header.bin and footer.bin to the person on the other end'
	
	#md5 sum the map for checking
	m = hashlib.md5()	
	m.update(header + body + footer)
	sum = m.digest()
	
	#write the sum to sum.txt
	with open('sum.txt', 'w') as f:
		f.write(sum)
	
	print 'Your md5 checksum of the map has been calculated and written to sum.txt'
	print 'Please send this checksum to the person on the other end'
	
	raw_input('You are finished')
	return

#main
def main():
	
	if len(sys.argv) == 2:
		#create from instructions
		create_from_instructions()
		modify_from_instructions()
		
		return
		
	elif len(sys.argv) == 1:
		#create instructions
		create_instructions()
		create_from_instructions()
		modify_instructions()
		return
	else:
		print 'Improper number of arguments'
		return

DELIM = '|'
INSTRUCTIONS = 'instructions.txt'

main()