#!/usr/bin/env python3
# (c) Copyright 2017 Josh Wright
max = 120
import os, sys

def print_arg_narg(prefix=''):
	print('#ifndef '+prefix+'ARG')
	print('#define '+prefix+'ARG(', end='')
	for i in range(max):
		print("_%i, " % i, end = '')
	print("...) _%i" % (max-1))
	print('#endif')
	
	print('#ifndef '+prefix+'NARG')
	print('#define '+prefix+'NARG(...) '+prefix+'ARG(__VA_ARGS__', end='')
	for i in range(max):
		print(", %i" % (max - i - 1), end = '')
	print(")")
	print('#endif')

if __name__ == '__main__':
	print("#pragma once")
	print_arg_narg()
