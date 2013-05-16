#!/usr/bin/python

# Francisco Jose Sanchez Sanchez
#
# francjsanchez@gmail.com
#
# Tuenti Challenge 3, Challenge 8
# 
# Solution: hack strcmp with an array object.

import urllib

key = raw_input()

url = "http://pauth.contest.tuenti.net/"
method = "POST"
params = {"key": key, "pass[]": ""}

params = urllib.urlencode(params)
f = urllib.urlopen(url, params)
print (f.read(), f.code)[0].split()[-1]
