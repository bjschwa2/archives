""" Course page lister. Looks at all file starting with ac and
treats it as an standard web log file. Reports on all domains that
have visited a course description page"""

import os
import re
from hname import *

shorttable = {}
ctable = {}
lookfor = re.compile("GET\s/course/([a-z]+)")

for filename in os.listdir("."):
   if not filename.startswith("ac"):
      continue # eliminate files that are not logfiles
   for line in open(filename).xreadlines():
      parts = line.split(" ")
# How much of the name / IP address do we report?
      host = hname(parts[0])
      dpsumm = host.getShort()
# Count the host usage and log any course files
      shorttable[dpsumm] = 1 + shorttable.get(dpsumm,0)
      gotten = lookfor.findall(line)
      if (not gotten): continue
      ctable[dpsumm] = ctable.get(dpsumm,"") + " " + gotten[0]

def byhits(one,two):
   global shorttable
   return shorttable[two].__cmp__(shorttable[one])

visitors = ctable.keys()
visitors.sort(byhits)

for browser in visitors:
   print browser,ctable[browser],shorttable[browser]