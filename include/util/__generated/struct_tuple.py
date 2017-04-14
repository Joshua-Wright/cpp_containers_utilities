#!/usr/bin/env python3
# (c) Copyright 2017 Josh Wright
max = 120

print("#pragma once")

print("""
#define __FIELDS_0(T)""")
for i in range(1,max+1):
    print("#define __FIELDS_%i(T" % i,  end='')
    for j in range(1,i+1):
        print(",a%i" % j, end='')
    print(') \\')
    print("\tDEFINE_GET(T, a%i, %i) \\" % (i,i-1))
    print("\t__FIELDS_%i(T" % (i - 1), end='')
    for j in range(1,i):
        print(",a%i" % j, end='')
    print(")")
