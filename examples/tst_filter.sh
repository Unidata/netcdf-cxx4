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

# Function to remove selected -s attributes from file;
# These attributes might be platform dependent
sclean() {
    cat $1 \
	| sed -e '/:_Endianness/d' \
	| sed -e '/_NCProperties/d' \
	| sed -e '/_SuperblockVersion/d' \
	| sed -e '/_IsNetcdf4/d' \
	| cat > $2
}

# Function to extract _Filter attribute from a file
# These attributes might be platform dependent
getfilterattr() {
sed -e '/var.*:_Filter/p' -ed <$1 >$2
}

trimleft() {
sed -e 's/[ 	]*\([^ 	].*\)/\1/' <$1 >$2
}


# Locate the plugin path and the library names; argument order is critical
# Find bzip2 and capture
findplugin h5bzip2
BZIP2PATH="${HDF5_PLUGIN_PATH}/${HDF5_PLUGIN_LIB}"
# Find misc and capture
findplugin misc
MISCPATH="${HDF5_PLUGIN_PATH}/${HDF5_PLUGIN_LIB}"

echo "final HDF5_PLUGIN_PATH=${HDF5_PLUGIN_PATH}"
echo "final HDF5_PLUGIN_PATH=${HDF5_PLUGIN_PATH}"
export HDF5_PLUGIN_PATH

# Verify
if ! test -f ${BZIP2PATH} ; then echo "Unable to locate ${BZIP2PATH}"; exit 1; fi
if ! test -f ${MISCPATH} ; then echo "Unable to locate ${MISCPATH}"; exit 1; fi

echo "**** Testing plugin write"

rm -f pres_temp_plugin_4D.nc
${execdir}/pres_temp_4D_plugin_wr

echo "**** Testing plugin read"
${execdir}/pres_temp_4D_plugin_rd

exit 0
