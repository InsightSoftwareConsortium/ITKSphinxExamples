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

### Print ITK Module Loading

# It can be useful to see how ITK modules are being loaded in order
# to understand module dependencies. `itk.auto_progress` can be used
# to increase verbosity of module loading and filter printouts.

import itk

# Enable module loading printouts
itk.auto_progress(2)

# Load a filter from a module with several dependencies
_ = itk.ForwardFFTImageFilter.values()[0].New()

# Disable printouts
itk.auto_progress(0)

# Do work
