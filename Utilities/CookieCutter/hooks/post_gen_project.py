#!/usr/bin/env python

# Copyright Insight Software Consortium
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


""" Post-generate hook script to incorporate the example to the source tree.
"""

import os
import shutil
import sys


def get_group_and_module_from_class_name(itk_dir, class_name):
    """ Get the ITK group and module a class belongs to.

    Parameters
    ----------
    itk_dir : str
        ITK source directory.
    class_name : str
        ITK class name.
    Returns
    -------
    result : dict
        Dictionary containing a boolean telling if the ITK module and group were
        found, and the ITK group and module names found.
    """

    cmakefile = os.path.join(itk_dir, 'CMake', 'UseITK.cmake')
    result = dict()
    result['bool'] = False

    if class_name is None:
        return result

    if not os.path.exists(cmakefile):
        print ('Error: wrong path')
    else:
        path = ''

        for root, dirs, files in os.walk(os.path.join(itk_dir, 'Modules')):
            for f in files:
                if f == 'itk' + class_name + '.h':
                    path = root

        if len(path) != 0:

            temp = path.split(os.path.sep)
            depth = len(temp)

            result['Module'] = temp[depth - 2]
            result['Group'] = temp[depth - 3]
            result['bool'] = True

        else:
            print ('Error: this class is not part of itk')

    return result


def main():

    # Find the ITK module and group name
    class_name = '{{ cookiecutter.class_name }}'
    itk_dir = ''

    temp_res = get_group_and_module_from_class_name(itk_dir, class_name)

    while not temp_res['bool']:
        class_name = get_input("Please enter a class: ")
        class_name = itkcorrect(class_name)

        temp_res = get_group_and_module_from_class_name(
            args.itk_source_dir, class_name)

    group_name = temp_res['Group']
    module_name = temp_res['Module']

    # Move the example to the appropriate place
    src = ''
    dest = '../../../src/group_name/module_name/' + '{{ cookiecutter.example_name }}
    shutil.move(src, dest)


if __name__ == '__main__':
    main()
