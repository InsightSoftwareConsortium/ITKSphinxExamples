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

import argparse
import itk

parser = argparse.ArgumentParser(description="Set the Default Number Of Threads.")
parser.add_argument("number_of_threads", type=int)
args = parser.parse_args()

# Create a MultiThreaderBase instance to get access to its static methods
threader = itk.MultiThreaderBase.New()
threader.SetGlobalDefaultNumberOfThreads(args.number_of_threads)

filt = itk.MedianImageFilter.New()
filter_default_threads = filt.GetMultiThreader().GetGlobalDefaultNumberOfThreads()

print("Filter's default number of threads: {}".format(filter_default_threads))

assert filter_default_threads == args.number_of_threads
