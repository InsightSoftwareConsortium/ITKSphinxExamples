#!/usr/bin/env python

# Copyright NumFOCUS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#        https://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
import itk
import argparse

from distutils.version import StrictVersion

if StrictVersion(itk.Version.GetITKVersion()) < StrictVersion("5.2.0"):
    print("ITK 5.2.0 is required.")
    sys.exit(1)

parser = argparse.ArgumentParser(description="Convert An itk Image to vtk Image Data.")
parser.add_argument("input_image")
args = parser.parse_args()

inputImage = itk.imread(args.input_image)

vtkImage = itk.vtk_image_from_image(inputImage)

print(vtkImage)
