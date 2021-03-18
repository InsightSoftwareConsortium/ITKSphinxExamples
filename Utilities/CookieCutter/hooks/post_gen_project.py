#!/usr/bin/env python

# Copyright NumFOCUS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


""" Post-generate cookiecutter hook script to incorporate the example to the
    ITKSphinxExamples source tree.
"""

import os
import shutil

from os.path import join as pjoin


def add_new_group(itk_examples_src, group_name):
    """Add a new group to the ITKSphinxExamples.

    Parameters
    ----------
    itk_examples_src : str
        ITK examples source directory.
    group_name : str
        ITK group name.
    """

    # Populate ITKSphinxExamples/src/$group_name/CMakeLists.txt
    f = open(pjoin(itk_examples_src, group_name, "CMakeLists.txt"), "a+")
    f.write("add_subdirectory(" + group_name + ") \n")

    f.write("")
    f.close()

    # Populate ITKSphinxExamples/src/$group_name/index.rst
    f = open(pjoin(itk_examples_src, group_name, "index.rst"), "a+")
    f.write(group_name + "\n")
    for i in range(len(group_name)):
        f.write("=")
    f.write("\n\n")

    f.write(".. toctree::\n")
    f.write("  :maxdepth: 2\n\n")
    f.close()


def add_new_module(itk_examples_src, group_name, module_name):
    """Add a new module to the ITKSphinxExamples.

    Parameters
    ----------
    itk_examples_src : str
        ITK examples source directory.
    group_name : str
        ITK group name.
    module_name : str
        ITK module name.
    """

    # Append 'add_subdirectory_if_module_enabled( $module_name )' to
    # ITKSphinxExamples/src/$group_name/CMakeLists.txt
    f = open(pjoin(itk_examples_src, group_name, "CMakeLists.txt"), "a+")
    f.write("add_subdirectory_if_module_enabled(" + module_name + ")\n")
    f.close()

    # Append '$module_name/index.rst' to
    # ITKSphinxExamples/src/$group_name/index.rst
    f = open(pjoin(itk_examples_src, group_name, "index.rst"), "a+")
    f.write("  " + module_name + "/index.rst\n")
    f.close()

    # Append 'add_example($example_name)' to
    # ITKSphinxExamples/src/$group_name/$module_name/CMakeLists.txt
    f = open(pjoin(itk_examples_src, group_name, module_name, "index.rst"), "a+")
    f.write(module_name + "\n")
    for i in range(len(module_name)):
        f.write("=")
    f.write("\n\n")

    f.write(".. toctree::\n")
    f.write("  :maxdepth: 1\n\n")
    f.close()


def add_example_to_module(itk_examples_src, group_name, module_name, example_name):
    """Add the example information to the ITKSphinxExamples module.

    Parameters
    ----------
    itk_examples_src : str
        ITK examples source directory.
    group_name : str
        ITK group name.
    module_name : str
        ITK module name.
    example_name : str
        ITK example name.
    """

    # Append 'add_example( $example_name )' to
    # ITKSphinxExamples/src/$group_name/$module_name/CMakeLists.txt
    f = open(pjoin(itk_examples_src, group_name, module_name, "CMakeLists.txt"), "a+")
    f.write("\nadd_example(" + example_name + ")\n")
    f.write(
        "compare_to_baseline(EXAMPLE_NAME "
        + example_name
        + "\n  BASELINE_PREFIX OutputBaseline\n  )\n"
    )
    f.close()

    # Append 'add_example($example_name)' to
    # ITKSphinxExamples/src/$group_name/$module_name/index.rst
    f = open(pjoin(itk_examples_src, group_name, module_name, "index.rst"), "a+")
    f.write("  " + example_name + "/Documentation.rst\n")
    f.close()


def print_instructions(itk_examples_src, example_dir, example_name, group_name):
    """Print instructions to edit files and contribute to ITKSphinxExamples.

    Parameters
    ----------
    itk_examples_src : str
        ITK examples source directory.
    example_dir : str
        ITK example directory.
    example_name : str
        ITK example name.
    group_name : str
        ITK group name.
    """

    example_cmakelists = pjoin(example_dir, "CMakeLists.txt")
    example_rst = pjoin(example_dir, "Documentation.rst")
    example_cxx = pjoin(example_dir, "Code.cxx")
    example_py = pjoin(example_dir, "Code.py")

    print("Example {} added successfully!".format(example_name))

    print("Please:")
    print("  1- Edit the following files:")
    print("    * " + example_cxx)
    print("    * " + example_py)
    print("    * " + example_cmakelists)
    print("    * " + example_rst + "\n")

    print("  2- Commit changes in the ITKSphinxExamples source directory and push:")
    print("    $ cd " + itk_examples_src)
    print("    $ git checkout -b Add" + example_name)
    print("    $ git add " + group_name)
    print('    $ git commit -a -m "ENH: Add ' + example_name + '" ')
    print("    $ git push origin Add" + example_name)


def main():

    # Get the cookiecutter template variables
    group_name = "{{ cookiecutter.group_name }}"
    module_name = "{{ cookiecutter.module_name }}"
    example_name = "{{ cookiecutter.example_name }}"
    itk_examples_src = "{{ cookiecutter.itk_examples_src }}"

    example_dest_dir = pjoin(itk_examples_src, group_name, module_name, example_name)

    # Add the example data to the corresponding group and module files
    output_dir = os.getcwd()

    # If ITKExmaples/src/$group_name/$module_name/$example_name does not exist
    if not os.path.exists(example_dest_dir):

        # If ITKSphinxExamples/src/$group_name does not exist
        if not os.path.exists(pjoin(itk_examples_src, group_name)):

            # Create directory ITKSphinxExamples/src/$group_name
            os.mkdir(pjoin(itk_examples_src, group_name))

            # Add new group
            add_new_group(itk_examples_src, group_name)

        # If ITKSphinxExamples/src/$group_name/$module_name does not exist
        if not os.path.exists(pjoin(itk_examples_src, group_name, module_name)):

            # Create directory ITKSphinxExamples/src/$group_name/$module_name
            os.mkdir(pjoin(itk_examples_src, group_name, module_name))

            # Add new module
            add_new_module(itk_examples_src, group_name, module_name)

        # Add example information to module
        add_example_to_module(itk_examples_src, group_name, module_name, example_name)

        # Move the example to the appropriate place in the ITKSphinxExamples source
        # tree
        shutil.move(output_dir, example_dest_dir)

        # Print instructions
        print_instructions(itk_examples_src, example_dest_dir, example_name, group_name)

    else:
        print(
            "Error: This example is already present in ITKSphinxExamples: {}".format(
                example_dest_dir
            )
        )

        # Delete the generated cookiecutter project
        shutil.rmtree(output_dir)


if __name__ == "__main__":
    main()
