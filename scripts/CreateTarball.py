#!/usr/bin/env python

""" Build tarballs for the examples.

Build the .tar.gz and .zip for the example, and copy them along with the
supporting files into the html output.

To be executed in the binary tree in the directory above the example.
"""

import glob
import os
import shutil
import sys
import tarfile
import zipfile


if len(sys.argv) < 3:
    print('usage: ' + sys.argv[0] + ' <example_name> <SPHINX_DESTINATION>')
    sys.exit(1)


# Collect our directories.
cwd = os.getcwd()
example_name = sys.argv[1]
example_dir = os.path.join(cwd, example_name)
example_idx = example_dir.index('/Examples/') + 1
html_output_dir = os.path.join(sys.argv[2], 'html', example_dir[example_idx:])


# Copy files to support web editting to the html output.
files_to_copy_to_html_output = []
files_to_copy_to_html_output.append(os.path.join(example_dir, 'CMakeLists.txt'))
files_to_copy_to_html_output.extend(glob.glob(os.path.join(example_dir, '*.cxx')))
files_to_copy_to_html_output.extend(glob.glob(os.path.join(example_dir, '*.py')))
files_to_copy_to_html_output.extend(glob.glob(os.path.join(example_dir, '*.rst')))
for path in files_to_copy_to_html_output:
    shutil.copy2(path, html_output_dir)


# Tarballs for users to download from the website.
files_for_tarball = files_to_copy_to_html_output

# Add a directory to build the project.
build_dir = os.path.join(example_dir, 'build')
if not os.path.exists(build_dir):
    os.mkdir(build_dir)
files_for_tarball.append(build_dir)

# Substitude CMAKE_CURRENT_BINARY_DIR for CMAKE_CURRENT_SOURCE_DIR in the
# tarball CMakeLists.txt.  This so the input images can be found.
tarball_cmakelist = os.path.join(example_dir, 'CMakeLists.txt.tarball')
with open(tarball_cmakelist, 'w') as new_list_file:
    with open(os.path.join(example_dir, 'CMakeLists.txt'), 'r') as old_list_file:
        for line in old_list_file:
            newline = line.replace('CMAKE_CURRENT_BINARY_DIR', 'CMAKE_CURRENT_SOURCE_DIR')
            new_list_file.write(newline)
files_for_tarball = files_for_tarball[1:]
files_for_tarball.append(tarball_cmakelist)

inputs = glob.glob(os.path.join(example_dir, '*.md5'))
for path in inputs:
    files_for_tarball.append(path[:-4])
with tarfile.open(os.path.join(html_output_dir, example_name + '.tar.gz'), \
        'w:gz', dereference=True) as tarfile:
    example_dir_idx = example_dir.index(example_name)
    def strip_path(tarinfo):
        tarinfo.name = tarinfo.name[example_dir_idx-1:]
        # Put the inputs and outputs into the build directory because the test
        # will not be able to find them otherwise.
        basename = os.path.basename(tarinfo.name)
        if basename == 'CMakeLists.txt.tarball':
                head, tail = os.path.split(tarinfo.name)
                tarinfo.name = os.path.join(head, 'CMakeLists.txt')
        return tarinfo
    for path in files_for_tarball:
        tarfile.add(path, filter=strip_path)

with zipfile.ZipFile(os.path.join(html_output_dir, example_name + '.zip'), \
        'w') as zipfile:
    example_dir_idx = example_dir.index(example_name)
    for path in files_for_tarball:
        arcname = path[example_dir_idx-1:]
        # Put the inputs and outputs into the build directory because the test
        # will not be able to find them otherwise.
        basename = os.path.basename(arcname)
        if basename == 'CMakeLists.txt.tarball':
                head, tail = os.path.split(arcname)
                arcname = os.path.join(head, 'CMakeLists.txt')
        zipfile.write(path, arcname)
