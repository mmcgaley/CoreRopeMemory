# English character frequency table including capitals and punctuation based on
# http://www.queensu.ca/psychology/hiplab/Publications/Recentpublications/Mewhort_RP_15.pdf

from operator import itemgetter

letterTable = [
("A" , 280937),
("a" , 5263779),
("B" , 169474),
("b" , 866156),
("C" , 229363),
("c" , 1960412),
("D" , 129632),
("d" , 2369820),
("E" , 138443),
("e" , 7741842),
("F" , 100751),
("f" , 1296925),
("G" , 93212),
("g" , 1206747),
("H" , 123632),
("h" , 2955858),
("I" , 223312),
("i" , 4527332),
("J" , 78706),
("j" , 65856),
("K" , 46580),
("k" , 460788),
("L" , 106984),
("l" , 2553152),
("M" , 259474),
("m" , 1467376),
("N" , 205409),
("n" , 4535545),
("O" , 105700),
("o" , 4729266),
("P" , 144239),
("p" , 1255579),
("Q" , 11659),
("q" , 54221),
("R" , 146448),
("r" , 4137949),
("S" , 304971),
("s" , 4186210),
("T" , 325462),
("t" , 5507692),
("U" , 57488),
("u" , 1613323),
("V" , 31053),
("v" , 653370),
("W" , 107195),
("w" , 1015656),
("X" , 7578),
("x" , 123577),
("Y" , 94297),
("y" , 1062040),
("Z" , 5610),
("z" , 66423) ]

letterTable.sort(key=itemgetter(1), reverse=True)

punctuationTable = [
("!" , 2178 ),
("\"" , 284671 ),
("#" , 10 ),
("$" , 51572 ),
("%" , 1993),
("&" , 6523),
("\'" , 204497),
("(" , 53398),
(")" , 53735),
("*" , 20716),
("+" , 309),
("," , 984969 ),
("-" , 252302),
("." , 946136 ),
("/" , 8161 ),
("0" , 546233 ),
("1" , 460946),
("2" , 333499),
("3" , 187606),
("4" , 192528),
("5" , 374413),
("6" , 153865),
("7" , 120094),
("8" , 182627),
("9" , 282364),
(":" , 54036),
(";" , 36727),
("<" , 82),
("=" , 22),
(">" , 83),
("?" , 12357),
("@" , 1),
]

punctuationTable.sort(key=itemgetter(1), reverse=True)


characterTable = letterTable + punctuationTable

characterList = [char[0] for char in characterTable]

print characterList
