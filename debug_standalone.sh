#!/bin/bash
# (c) Copyright 2017 Josh Wright

out="debug_standalone.h"

cat include/util/debug.h | grep -v '__generated/debug\.h' > $out

echo >> $out
echo "///////////////////////////////////////////////////////////////////////////////" >> $out
echo "///////////////////////////////////////////////////////////////////////////////" >> $out
echo "/// generated"                                                                   >> $out
echo >> $out

cat include/util/__generated/debug.h |grep -v pragma >> $out