#!/bin/sh

# EXAMPLE.  To be replaced.
OBJECT_STORES_DIR=~/dashboards/dashboard_tests/ExternalData

md5=$(md5sum $1 | cut -d ' ' -f 1)
echo $md5 > $1.md5
cp $1 $OBJECT_STORES_DIR/MD5/$md5
rm $1
