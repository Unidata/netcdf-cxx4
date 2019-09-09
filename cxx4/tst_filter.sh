#!/bin/sh

if test "x$srcdir" = x ; then srcdir=`pwd`; fi
. ../test_common.sh

# Which test cases to exercise
API=1
NG=1
NCP=1
UNK=1
NGC=1
MISC=1

# Load the findplugins function
. ${builddir}/findplugin.sh
echo "findplugin.sh loaded"
