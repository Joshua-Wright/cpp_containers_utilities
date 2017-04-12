#!/usr/bin/env python3
# (c) Copyright 2016 Josh Wright
max = 32

# print("#define ARG(", end='')
# for i in range(max):
# 	print("_%i, " % i, end = '')
# print("...) _%i" % (max-1))

# print("#define NARG(...) ARG(__VA_ARGS__", end='')
# for i in range(max):
#     print(", %i" % (max - i - 1), end = '')
# print(")")

# for i in range(1,max+1):
#     print("#define __KV_%i(a1" % i,  end='')
#     for j in range(2,i+1):
#         print(",a%i" % j, end='')
#         print(") \\\n\t__KV_0", end='')
#         for j in range(1,i+1):
#             print(".a(#a%i,a%i)" % (j,j), end='')
#             print()
print()
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
