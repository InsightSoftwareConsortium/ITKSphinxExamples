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

import sys
import itk

if len(sys.argv) != 3:
    print("Usage: " + sys.argv[0] + "<InputFileName> "
          "<OutputFileName>")
    sys.exit(1)

parser = argparse.ArgumentParser(description='{{ cookiecutter.example_title }}.')
parser.add_argument('input_image')
parser.add_argument('output_image')
args = parser.parse_args()

input_image = itk.imread(args.input_image)

output_image = itk.itkHelpers.camel_to_snake_case({{ cookiecutter.class_name }})(input_image)

itk.imwrite(output_image, args.output_image)
