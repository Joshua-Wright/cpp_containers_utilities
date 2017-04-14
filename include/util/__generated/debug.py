#!/usr/bin/env python3
# (c) Copyright 2017 Josh Wright
max = 120

print("#pragma once")

print("#define ARG(", end='')
for i in range(max):
	print("_%i, " % i, end = '')
print("...) _%i" % (max-1))

print("#define NARG(...) ARG(__VA_ARGS__", end='')
for i in range(max):
	print(", %i" % (max - i - 1), end = '')
print(")")

for i in range(1,max+1):
	print("#define __KV_%i(a1" % i,  end='')
	for j in range(2,i+1):
		print(",a%i" % j, end='')
	print(") \\\n\t__KV_0", end='')
	for j in range(1,i+1):
		print(".a(#a%i,a%i)" % (j,j), end='')
	print()
