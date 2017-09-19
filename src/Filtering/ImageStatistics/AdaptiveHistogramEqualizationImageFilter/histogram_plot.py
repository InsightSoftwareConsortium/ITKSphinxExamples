#!/usr/bin/env python

#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License")
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================

import os
import sys

import matplotlib.pyplot as plt
import matplotlib.image as mpimg


str(sys.argv)

img=mpimg.imread(sys.argv[1])

fig, ax = plt.subplots()

n, bins, patches = ax.hist(img.ravel(), bins=256, fc='k', ec='k')

ax.set_xlabel('Smarts')
ax.set_ylabel('Frequency')
ax.set_title(sys.argv[2])

base = os.path.basename(sys.argv[1])

output_figure_name = os.path.splitext(base)[0] + '_histogram.png'

fig.tight_layout()
plt.show()

fig.savefig(output_figure_name)