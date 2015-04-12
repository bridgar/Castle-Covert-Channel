#Castle Encode/Decode module
#Adapted to Python by Bridger Hahn from code written in VC++ by Rishab Nithyanand

#Inputs are: First- 0 or 1 for encode or decode and then Second- File Location

import linecache
import sys
import time
import os
import array
import copy
import math
import random

#binomial function
def nCr(n,r):
	f = math.factorial
	return f(n) / f(r) / f(n-r)

#Function to decode a list of bitstrings back into their integers using n, m encoding
#Returns a list of ints
def decode_bitstring(bitstrings, n, m):
	decoded = []
	for i in range(len(bitstrings)):
		mcopy = copy.copy(m)
		curr_bin = 0
		temp_decoded = 0
		for j in range(0,n):
			if(bitstrings[i][j:j+1] == '1'):
				curr_bin = nCr(n-j, mcopy)
				temp_decoded += curr_bin
				mcopy -= 1
		temp_decoded += 1
		decoded.append(temp_decoded)
	return decoded

#Function to encode a vector of bignums into a bitstring using n,m encoding
#integers is a list of ints
#n is 800
#m is an int, the number of 1s in the bitstring
#Returns a list of strings
def get_bitstring(integers, n, m):
	bitstrings = []
	curr_choices = 0
	tempbigint = 0
	for i in range(len(integers)):
		mcopy = copy.copy(m)
		tempbigint = integers[i]
		bitstrings.append("")
		for j in reversed(range(1,n+1)):
			curr_choices = nCr(j,mcopy)
			if(curr_choices < tempbigint):
				mcopy-=1
				tempbigint = tempbigint - curr_choices
				bitstrings[i] += '1'
			else:
				bitstrings[i] += '0'
	return bitstrings

#function to encode a chunk into an integer
#chunks is a list of strings
#Returns a list of integers
def get_integers(chunks):
	chunk_ints = []
	for i in range(len(chunks)):
		temp = 0
		for j in range(len(chunks[i])):
			#shift left 8
			temp *= 256
			temp += ord(chunks[i][j])
		
		chunk_ints.append(temp)
	return chunk_ints

#function to read a block of fixed size from a file
#returns the read string
def get_block(f, blocksize, offset):
	f.seek(offset)
	return f.read(blocksize)

#function to read the lines from a file
#returns a list of the lines
def read_bitstrings(f):
	lines = []
	line = f.readline()
	while(line != ''):
		if(line != '\n'):
			lines.append(line)
		line = f.readline()
	return lines

#function to return the floor of the log of an int
def floor_log(integer):
	f_log = 1
	square = 2
	while(square < integer):
		square = square * 2
		f_log+=1
	return f_log

#function to return the contents of a file in chunksize*10 blocks
#returns a list of strings
def get_contents(f, chunksize):
	contents = []
	f.read()
	size = f.tell()
	blocksize = chunksize * 10
	nblocks = size // blocksize
	finalblocksize = 0
	if(size % blocksize != 0):
		finalblocksize = size % blocksize
		nblocks+=1
	for i in range(0,nblocks):
		f.seek(i*blocksize)
		if(i == nblocks - 1):
			contents.append(f.read(finalblocksize))
		else:
			contents.append(f.read(blocksize))
	return contents

def write_encoding(encoding, f):
	for i in range(len(encoding)):
		f.write(encoding[i] + '\n')

def write_decoding(decoded, f):
	for i in range(len(decoded)):
		temp = decoded[i]
		temp_s = ''
		while(temp > 0):
			temp_s += chr(temp % 256)
			temp = temp // 256
		f.write(temp_s[::-1])

def test_encoding(content, decoded):
	for i in range(len(decoded)):
		temp = decoded[i]
		while(temp > 0):
			temp = temp // 256

#MAIN

num_buildings = 800


#encoding
if(sys.argv[1] == '0'):
	fin = open(sys.argv[2], 'r')
	fout = open(sys.argv[2] + "-encoded", 'w')
	
	fin.read()
	size = fin.tell()
	fin.seek(0)
	
	curr_byte = 0
	while(curr_byte < size):
		m = random.randint(1,200)
		if(curr_byte + m >= size):
			m = size - curr_byte;
		combinations = nCr(num_buildings, m)
		logf = floor_log(combinations)
		blocksize = logf // 8
		if(blocksize == 0):
			blocksize = 1
		content = []
		content.append(get_block(fin, blocksize, curr_byte))
		curr_byte += blocksize
		chunk_ints = get_integers(content)
		bitstring = get_bitstring(chunk_ints, num_buildings, m)
		decoded = decode_bitstring(bitstring, num_buildings, m)
		write_encoding(bitstring, fout)
	
#decoding
else:
	fin = open(sys.argv[2], 'r')
	fout = open(sys.argv[2] + "-decoded", 'w')
	
	bitstrings = read_bitstrings(fin)
	for i in range(len(bitstrings)):
		bitstring = [bitstrings[i][:-1]]
		m = bitstring[0].count('1')
		decoded = decode_bitstring(bitstring, num_buildings, m)
		write_decoding(decoded, fout)

fin.close()
fout.close()


































