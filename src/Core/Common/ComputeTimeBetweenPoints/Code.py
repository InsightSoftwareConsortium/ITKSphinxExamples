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

import itk


def LongFunction():
    # CPython loops are much slower than C++,
    # so a smaller range is used in this case.
    for i in range(int(1e5)):
        a = 0.0  # noqa: F841

clock = itk.TimeProbe()

clock.Start()
LongFunction()

clock.Stop()
print('Mean: ' + str(clock.GetMean()))
print('Total: ' + str(clock.GetTotal()))

clock.Start()
LongFunction()

clock.Stop()
print('Mean: ' + str(clock.GetMean()))
print('Total: ' + str(clock.GetTotal()))

clock.Report()
