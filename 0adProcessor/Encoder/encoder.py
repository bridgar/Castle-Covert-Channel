import linecache
import sys
import time
import os
import array
import copy
import math
import random
import struct

num_buildings = 800

random.seed(0)

#binomial function
def nCr(n,r):
    f = math.factorial
    if (n==r):
        return 1
    if (n < r):
        return 0
    else:
        return (f(n) // f(r)) // f(n-r)

#function to return the floor of the log of an int
def floor_log(integer):
    f_log = 1
    square = 2
    while(square < integer):
        square = square * 2
        f_log+=1
    return f_log
	
#function to read a block of fixed size from a file
#returns the read string
def get_block(f, blocksize, offset):
    f.seek(offset)
    return f.read(blocksize)
	
#function to encode a chunk into an integer
#chunk is a string
#Returns an integer
def get_integer(chunk):
    temp = 0
    for i in range(len(chunk)):
        #shift left 8
        temp *= 256
        temp += struct.unpack('B', chunk[i:i+1])[0]#ord(chunk[i:i+1])
    return temp

	
#Function to encode a bignum into a bitstring using n,m encoding
#int_in is an int, the int to be encoded
#m is an int, the number of 1s in the bitstring
#Returns a string
def get_bitstring(int_in, m):
    bit_array = num2choose(int_in, num_buildings, m)
    bitstring=''
    for i in bit_array:
        bitstring+=str(i)
    return bitstring

def decode_bitstring(bitstring):
    bit_array = list()
    for i in bitstring:
        if i.isdigit():
           bit_array.append(int(i))
    return choose2num(bit_array)
#def get_bitstring(int_in, m):
#    bitstring = ""
#    curr_choices = 0
#    micounter = 0
#    for i in reversed(range(1,num_buildings+1)):
#        #print "Encode. Binomial ("+str(i+1)+","+str(m)+")"
#        if(i >= 0 and m >= 0):
#            curr_choices = nCr(i,m)
#        else:
#            break
#        #if (m==0):
#        #    bitstring+='0'
#        if((curr_choices <= int_in) or (i == 1 and m == 1)):
#            m -= 1
#            bitstring += '1'
#            int_in -= curr_choices
#            #if(m==i):
#            #    int_in -= curr_choices
#            #    bitstring += '1'
#            #    while(m>1):
#            #        m -= 1
#            #        i -= 1
#            #        bitstring += '0'
#            #    #bitstring += '1'
#            #else:
#            #    m -= 1
#            #    int_in -= curr_choices
#            #    bitstring += '1'
#        else:
#            bitstring += '0'
#    #print "m==i happened: "+str(micounter)+" times"
#    print "Remaining int_in: "+str(int_in)
#    return bitstring[::-1]
#	
#Function to decode a bitstring back into an integer using n, m encoding
#Returns an int
#def decode_bitstring(bitstring):
#    decoded = 0
#    m = 1
#    for i in range(0,len(bitstring)):
#        if(bitstring[i] == '1'):
#            #print "Decode. Selecting "+str(i)+"th element"
#            #print "Decode. Binomial ("+str(i+1)+","+str(m)+")"
#            curr_bin = nCr(i+1, m)
#            decoded += curr_bin
#            m += 1
#    return decoded

def num2choose(num,n,k):
#    """ num2choose(num,n,k) - from a list of the k-subsets (combinations) from a
#   set with n elements, return the numth element.  Represent the combination as a
#   bit vector."""
    if (n < k) or (k < 0): raise ValueError("num2choose: " + str(n) + ", " +str(k))
    if (n==k): return [1]*n  # base case of form [1,1,...]
    if (k==0): return [0]*n  # base case of form [0,0,...]
    num %= nCr(n,k)
    thedigit = 0
    sum = 0
    for thedigit in range(n-k+1):
        oldsum = sum
        sum += nCr(n-1-thedigit,k-1)
        if (num < sum):
            return [0]*thedigit + [1] + num2choose(num-oldsum, n-(thedigit+1),k-1)


def choose2num(thelist):
#    """ choose2num(thelist) - Given a bit vector and thinking of it as a
#    combination (aka k-subset) from a set with n elements, return the order of this
#   element in the list of all (n choose k) such combinations."""
    if(len([thelist[i] for i in range(len(thelist)) if ((thelist[i] != 0) and (thelist[i] != 1))]) > 0): 
        raise ValueError("choose2num(" + thelist + ") expecting list entries {0,1}")
    n = len(thelist)
    k = sum(thelist) # total number of 1's
    if ((n==0) or (k==0) or (n==k)): 
        return 0 # base cases of form [], [0,0,...] or [1,1,...]
    num = 0
    for firstbit in range(n-k+1):
        if (thelist[firstbit] == 1):
            return num + choose2num(thelist[firstbit+1:])
        num += nCr(n-firstbit-1,k-1)

def write_encoding(encoding, f):
    f.write(encoding + '\n')

def read_bitstrings(f):
    lines = []
    line = f.readline()
    while(line != ''):
        if(line != '\n'):
            lines.append(line)
        line = f.readline()
    return lines		
		
def write_decoding(decoded, f):
    temp_s = ''
    while(decoded != 0):
        temp_s += chr(decoded % 256)
        decoded = decoded // 256
    f.write(temp_s[::-1])

def return_decoded_string(decoded):
    temp_s = ''
    while(decoded > 0):
        temp_s += chr(decoded%256)
        decoded=decoded//256
    return temp_s[::-1]	
#MAIN


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
        #if(curr_byte + m >= size):
        #    m = size - curr_byte;
        combinations = nCr(num_buildings, m)
        logf = floor_log(combinations)
        blocksize = logf // 8
        if(blocksize == 0):
            blocksize = 1
	if(curr_byte + blocksize >= size):
            blocksize = size - curr_byte;
            logf = blocksize * 8
            logf = 2**logf
            m = 1
            while(nCr(num_buildings, m) < logf):    
                m += 1
            last_block = 1
        else:
            last_block = 0
        
        #while(True):
        #    if((floor_log(nCr(num_buildings,m-1))//8) == blocksize):
        #        print "\nm: "+str(m)+", m-1: "+str(m-1)+", blocksize: "+str(blocksize) +", new blocksize: "+str(floor_log(nCr(num_buildings,m-1))//8);
        #        m = m - 1
        #    else:
        #        break    
        #print "\n\nm: "+str(m)

        content = get_block(fin, blocksize, curr_byte)
        curr_byte += blocksize
        chunk_int = get_integer(content)
        bitstring = get_bitstring(chunk_int, m)
        decoded = decode_bitstring(bitstring)
        if(content != return_decoded_string(decoded)):
            no_match = 1
        else:
            no_match = 0
        write_encoding(bitstring, fout)
	
#decoding
else:
    fin = open(sys.argv[2], 'r')
    fout = open(sys.argv[2] + "-decoded", 'w')
    bitstrings = read_bitstrings(fin)
    #print bitstrings
    for i in range(len(bitstrings)):
        bitstring = bitstrings[i]
        m = bitstring[0].count('1')
        decoded = decode_bitstring(bitstring)
        write_decoding(decoded, fout)
fin.close()
fout.close()
