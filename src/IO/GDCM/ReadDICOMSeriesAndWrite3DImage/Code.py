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
import os

import itk

if len(sys.argv) < 2:
    print("Usage: " + sys.argv[0] +
          " [DicomDirectory [outputFileName [seriesName]]]")
    print("If DicomDirectory is not specified, current directory is used\n")

# current directory by default
dirName = '.'
if len(sys.argv) > 1:
    dirName = sys.argv[1]

PixelType = itk.ctype('signed short')
Dimension = 3

ImageType = itk.Image[PixelType, Dimension]

namesGenerator = itk.GDCMSeriesFileNames.New()
namesGenerator.SetUseSeriesDetails(True)
namesGenerator.AddSeriesRestriction("0008|0021")
namesGenerator.SetGlobalWarningDisplay(False)
namesGenerator.SetDirectory(dirName)

seriesUID = namesGenerator.GetSeriesUIDs()

if len(seriesUID) < 1:
    print('No DICOMs in: ' + dirName)
    sys.exit(1)

print('The directory: ' + dirName)
print('Contains the following DICOM Series: ')
for uid in seriesUID:
    print(uid)

seriesFound = False
for uid in seriesUID:
    seriesIdentifier = uid
    if len(sys.argv) > 3:
        seriesIdentifier = sys.argv[3]
        seriesFound = True
    print('Reading: ' + seriesIdentifier)
    fileNames = namesGenerator.GetFileNames(seriesIdentifier)

    reader = itk.ImageSeriesReader[ImageType].New()
    dicomIO = itk.GDCMImageIO.New()
    reader.SetImageIO(dicomIO)
    reader.SetFileNames(fileNames)

    writer = itk.ImageFileWriter[ImageType].New()
    outFileName = os.path.join(dirName, seriesIdentifier + '.nrrd')
    if len(sys.argv) > 2:
        outFileName = sys.argv[2]
    writer.SetFileName(outFileName)
    writer.UseCompressionOn()
    writer.SetInput(reader.GetOutput())
    print('Writing: ' + outFileName)
    writer.Update()

    if seriesFound:
        break
