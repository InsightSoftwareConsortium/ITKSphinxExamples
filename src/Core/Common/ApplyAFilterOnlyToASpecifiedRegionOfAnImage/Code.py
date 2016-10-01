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
#==========================================================================*/

import itk

Dimension = 2
PixelType = itk.F
ImageType = itk.Image[PixelType, Dimension]

smallSize = itk.Size[Dimension]()
smallSize.Fill(10)

index = itk.Index[Dimension]()
index.Fill(0)

region = itk.ImageRegion[Dimension]()
region.SetIndex(index)
region.SetSize(smallSize)

bigSize = itk.Size[Dimension]()
bigSize.Fill(10)

RandomSourceType = itk.RandomImageSource[ImageType]
randomImageSource = RandomSourceType.New()
randomImageSource.SetNumberOfThreads(1)  # to produce non-random results
randomImageSource.SetSize(bigSize)
randomImageSource.GetOutput().SetRequestedRegion(region)

print("Created random image.")

DerivativeImageFilterType = itk.DerivativeImageFilter[ImageType, ImageType]

derivativeFilter = DerivativeImageFilterType.New()
derivativeFilter.SetInput(randomImageSource.GetOutput())
derivativeFilter.SetDirection(0)  # "x" axis
derivativeFilter.GetOutput().SetRequestedRegion(region)
derivativeFilter.Update()

print("Computed derivative.")
