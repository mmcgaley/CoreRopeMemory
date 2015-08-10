# coding=UTF-8
#
# generate a list of all 8 bit binary strings,
# sort them by how "pretty" they will be in 
# Core Rope Memory
#
# mmcgaley@gmail.com
# 2015.04.19
#

WORDLEN = 7
import math

def addLeadingZeros(binaryString) :
        return ((WORDLEN - len(binaryString)) * "0") + binaryString

def maxZeros(binaryString) :
        zeroCount = 0
        maxZeroCount = 0

        for bit in list(binaryString) :
                if bit is "0" : zeroCount += 1
                else :
                        if (zeroCount > maxZeroCount) :
                                maxZeroCount = zeroCount
                        zeroCount = 0

        if (zeroCount > maxZeroCount) :
                maxZeroCount = zeroCount

        return maxZeroCount

def totalZeros(binaryString) :
        return len([x for x in binaryString if x is '0'])

def zeroBalance(binaryString) :
        zeroCount = 0
        symmetricalCentre = int(math.ceil(len(binaryString)/2.0))

        firstHalf = binaryString[:len(binaryString)/2]
        secondHalf = binaryString[symmetricalCentre:]

        return abs(totalZeros(firstHalf) - totalZeros(secondHalf)) # absolute value

def charSortKey(tableEntry):
        (c, _) = tableEntry
        if c.islower():
                return 0 + ord(c)
        elif c.isupper():
                return 1000 + ord(c)
        elif c.isspace():
                return 2000 + ord(c)
        elif c.isdigit():
                return 3000 + ord(c)
        else:
                # Cf. https://docs.python.org/2/library/stdtypes.html#str.decode
                u = c.decode('utf-8')
                return 4000 + ord(u)

## main :)

binaryStringsList = []
#for b in range(1, 256): starting at 1 because 0000000 is a special character
for b in range(1, pow(2, WORDLEN)):
        binaryStringsList.append(addLeadingZeros(bin(b)[2:])) # strip "0b" from beginning 

binaryStringsList.sort(key=totalZeros)
binaryStringsList.sort(key=maxZeros)
binaryStringsList.sort(key=zeroBalance)

# character ordering based on frequency_table.py in this directory
characterList = ['e', 't', 'a', 'o', 'n', 'i', 's', 'r', 'h', 'l', 'd', 'c',
'u', 'm', 'f', 'p', 'g', 'y', 'w', 'b', 'v', 'k', ' ', 'T', 'S', 'A', 'M', 'C', 'I',
'N', 'B', 'R', 'P', 'E', 'D', 'H', 'x', 'W', 'L', 'O', 'F', 'Y', 'G', 'J', 'z',
'j', 'U', 'q', 'K', 'V', 'Q', 'X', 'Z', 'á', 'é', 'í', 'ó', 'ú', 'Á', 'É', 'Í',
'Ó', 'Ú', ',', '.', '0', '1', '5', '2', '"', '9', '-', "'", '4', '3', '8', '6',
'7', ':', ')', '(', '$', ';', '*', '?', '/', '&', '!', '%', '+', '>', '<', '=',
'#', '@']

characterBinaryTable = zip(characterList, binaryStringsList)
characterBinaryTable.sort(key=charSortKey)
for mapping in characterBinaryTable:
   print "\'%s\' => \'%s\'," % mapping # for PHP array creation
