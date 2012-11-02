#!/usr/bin/env python

""" Build a .tar.gz and .zip for the given input directory and output prefix.

The basename of the output prefix is used at the top level of the tarball
instead of the input directory.

./DocumentationTarball.py /path/to/html/ /path/to/output_prefix

will create

/path/to/output_prefix.tar.gz
/path/to/output_prefix.zip

that each contain output_prefix/* where * is the contents of /path/to/html.
"""

import os
import sys
import tarfile
import zipfile

if len(sys.argv) < 3:
    print('usage: ' + sys.argv[0] + ' input_directory output_prefix')
    sys.exit(1)

input_dir = sys.argv[1]
output_prefix = sys.argv[2]

tarball_top_dir = os.path.basename(output_prefix)

with tarfile.open(output_prefix + '.tar.gz', 'w:gz', dereference=True) as tar:
    for path in os.listdir(input_dir):
        tar.add(path, arcname=os.path.join(tarball_top_dir, path))

with zipfile.ZipFile(output_prefix + '.zip', 'w') as zip:
    for path, dirs, files in os.walk(input_dir):
        for fname in files:
            name = os.path.join(path, fname)
            arcname = os.path.join(tarball_top_dir, name[len(input_dir)+1:])
            zip.write(name, arcname)

