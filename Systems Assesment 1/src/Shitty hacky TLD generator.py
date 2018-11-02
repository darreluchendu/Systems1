import sys
import random
from urllib2 import urlopen
import string
from time import mktime,strptime,strftime,localtime,gmtime
from math import sqrt
from collections import defaultdict
from tqdm import tqdm
from os import linesep
from multiprocessing.pool import ThreadPool as Pool

def strTimeProp(start, end, format, prop):
    stime = mktime(strptime(start, format))
    etime = mktime(strptime(end, format))

    ptime = stime + prop * (etime - stime)

    return strftime(format, localtime(ptime))


def randomDate(start, end, prop):
    return strTimeProp(start, end, '%d/%m/%Y', prop)


# usage gen_tld.py START_DATE END_DATE NUMBER_OF_LINES
f = open("enormous.txt", "w")
o = open("enormous.out", "w")


data = urlopen("http://data.iana.org/TLD/tlds-alpha-by-domain.txt")
dictionary = urlopen("https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt")

begin = input("Start date to generate from (dd/mm/yyyy): ")
if not begin:
    begin = "01/01/1970"
end = input("End date to generate to (dd/mm/yyyy inclusive): ")
if not end:
    end = strftime("%d/%m/%Y", gmtime())
n = input("How many entries to generate? ")
if not n:
    n = 50000

tldlist = list()
namelist = [str(x)[2:-5] for x in dictionary]

for line in data:
    line = str(line)
    tldlist.append(line[2:-3].lower())

tldlist = tldlist[1:]
tldlist = tldlist[:1361] + tldlist[1512:]

rand = int(input("How many TLD's?: ") or len(tldlist))
if (rand>0):
    indices = random.sample(range(len(tldlist)), rand)
    tldlist = [tldlist[i] for i in sorted(indices)]

distro = int(input("No Distrobution(0), Gaussian(1) or Exponential(2)?: ") or 0)

d = defaultdict(int)
if (distro==1):
    ws = [random.gauss(10*sqrt(int(n)),2.718*sqrt(int(n))) for _ in range(len(tldlist))]
elif (distro==2):
    ws = [random.expovariate(10*sqrt(int(n))) for _ in range(len(tldlist))]
else:
    ws = [random.random() for _ in range(len(tldlist))]

tldran = random.choices(tldlist, weights=ws, k=int(n))

for i in tqdm(range(int(n))):
    d[tldran[i]] += 1
    output = (randomDate(begin,end,random.random()))
    output += " %s.%s.%s" % (random.choice(namelist),random.choice(namelist), tldran[i])
    output += linesep
    f.write(output)

print("Saved entries to enormous.txt")

f.close()

s = sum(d.values())
prn = list()
for k,v in d.items():
    pct = v * 100.00 / s
    out = '  {0:.2f}'.format(pct)
    out = out + " " + str(k) + linesep
    prn.append(out)

prn.sort()
for i in prn:
    o.write(i)

print("Saved resultes to enormous.out")
