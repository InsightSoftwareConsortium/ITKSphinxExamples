#!/usr/bin/env python

""" Build archives for the examples.

Build the .tar.gz and .zip for the example, and copy them along with the
supporting files into the html output.

To be executed in the binary tree in the directory above the example.
"""

import glob
import os
import shutil
import sys
import zipfile
from pathlib import Path


if len(sys.argv) != 3:
    print("usage: " + sys.argv[0] + " <example_name> <SPHINX_DESTINATION>")
    sys.exit(1)

# Collect our directories.
cwd = Path(os.getcwd())

example_name = sys.argv[1]
base_dir = cwd.parent.parent.parent
example_dir = str(cwd / example_name)
example_relative_path = cwd.relative_to(base_dir) / example_name
html_output_dir = str(Path(sys.argv[2]) / "html" / example_relative_path)

if not os.path.exists(html_output_dir):
    os.makedirs(html_output_dir)

# Copy files to support web editting to the html output.
files_to_copy_to_html_output = []
files_to_copy_to_html_output.append(os.path.join(example_dir, "CMakeLists.txt"))
files_to_copy_to_html_output.extend(glob.glob(os.path.join(example_dir, "*.cxx")))
files_to_copy_to_html_output.extend(glob.glob(os.path.join(example_dir, "*.html")))
files_to_copy_to_html_output.extend(glob.glob(os.path.join(example_dir, "*.py")))
files_to_copy_to_html_output.extend(glob.glob(os.path.join(example_dir, "*.ipynb")))
files_to_copy_to_html_output.extend(glob.glob(os.path.join(example_dir, "*.rst")))
for path in files_to_copy_to_html_output:
    shutil.copy2(path, html_output_dir)

# archives for users to download from the website.
files_for_archive = files_to_copy_to_html_output

# Add a directory to build the project.
build_dir = os.path.join(example_dir, "build")
if not os.path.exists(build_dir):
    os.mkdir(build_dir)
files_for_archive.append(build_dir)

# Substitude CMAKE_CURRENT_BINARY_DIR for CMAKE_CURRENT_SOURCE_DIR in the
# archive CMakeLists.txt.  This so the input images can be found.
archive_cmakelist = os.path.join(example_dir, "CMakeLists.txt.archive")
with open(archive_cmakelist, "w") as new_list_file:
    with open(os.path.join(example_dir, "CMakeLists.txt"), "r") as old_list_file:
        for line in old_list_file:
            newline = line.replace(
                "CMAKE_CURRENT_BINARY_DIR", "CMAKE_CURRENT_SOURCE_DIR"
            )
            new_list_file.write(newline)
files_for_archive = files_for_archive[1:]
files_for_archive.append(archive_cmakelist)

inputs = glob.glob(os.path.join(example_dir, "*.cid"))
for path in inputs:
    files_for_archive.append(path[:-4])

# Remove duplicates.
files_for_archive = set(files_for_archive)

with zipfile.ZipFile(
    os.path.join(html_output_dir, example_name + ".zip"), "w"
) as zipfile:
    example_dir_idx = example_dir.index(example_name)
    for path in files_for_archive:
        arcname = path[example_dir_idx - 1 :]
        # Put the inputs and outputs into the build directory because the test
        # will not be able to find them otherwise.
        basename = os.path.basename(arcname)
        if basename == "CMakeLists.txt.archive":
            head, tail = os.path.split(arcname)
            arcname = os.path.join(head, "CMakeLists.txt")
        zipfile.write(path, arcname)
