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
