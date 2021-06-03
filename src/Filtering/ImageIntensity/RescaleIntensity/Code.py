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

import sys
import itk

if len(sys.argv) != 5:
    print(
        "Usage: "
        + sys.argv[0]
        + " <InputFileName> <OutputFileName> <OutputMin> <OutputMax>"
    )
    sys.exit(1)

input_image = sys.argv[1]
output_image = sys.argv[1]
output_minimum = int(sys.argv[3])
output_maximum = int(sys.argv[4])

image = itk.imread(sys.argv[1])

image = itk.rescale_intensity_image_filter(
    image, output_minimum=output_minimum, output_maximum=output_maximum
)

itk.imwrite(image, sys.argv[2])
