#!/usr/bin/env python3
# (c) Copyright 2017 Josh Wright
import preprocessor_utils
max = 120
preprocessor_utils.max = max

def print_kv_chain():
	for i in range(1,max+1):
		print("#define __KV_%i(a1" % i,  end='')
		for j in range(2,i+1):
			print(",a%i" % j, end='')
		print(") \\\n\t__KV_0", end='')
		for j in range(1,i+1):
			print(".a(#a%i,a%i)" % (j,j), end='')
		print()

if __name__ == '__main__':
	print("#pragma once")
	preprocessor_utils.print_arg_narg('DEBUG_')
	print_kv_chain()
