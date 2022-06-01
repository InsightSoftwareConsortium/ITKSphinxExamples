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

parser = argparse.ArgumentParser(description="Read And Print DICOM Tags.")
parser.add_argument(
    "dicom_directory",
    nargs="?",
    help="If DicomDirectory is not specified, current directory is used",
)
args = parser.parse_args()

# current directory by default
dirName = "."
if args.dicom_directory:
    dirName = args.dicom_directory

# Setup the image readers with their type
PixelType = itk.ctype("signed short")
Dimension = 3

ImageType = itk.Image[PixelType, Dimension]

# Using GDCMSeriesFileNames to generate the names of
# DICOM files.
namesGenerator = itk.GDCMSeriesFileNames.New()
namesGenerator.SetUseSeriesDetails(True)
namesGenerator.SetDirectory(dirName)

# Get the names of files
fileNames = namesGenerator.GetInputFileNames()

# Setup the image series reader using GDCMImageIO
reader = itk.ImageSeriesReader[ImageType].New()
dicomIO = itk.GDCMImageIO.New()
dicomIO.LoadPrivateTagsOn()
reader.SetImageIO(dicomIO)
reader.SetFileNames(fileNames)

# Attempt to read the series, exit if unable to.
try:
    reader.Update()
except:
    print("Error occured while reading DICOMs in: " + dirName)
    sys.exit(1)

# ITK internally queries GDCM and obtains all the DICOM tags from the file
# headers. The tag values are stored in the MetaDataDictionary
# which is a general-purpose container for \{key,value\} pairs. The Metadata
# dictionary can be recovered from any ImageIO class by invoking the
# GetMetaDataDictionary() method.
metadata = dicomIO.GetMetaDataDictionary()

# Print the key value pairs from the metadadictionary
tagkeys = metadata.GetKeys()

for tagkey in tagkeys:
    # Note the [] operator for the key
    try:
        tagvalue = metadata[tagkey]
        print(tagkey + "=" + str(tagvalue))
    except RuntimeError:
        # Cannot pass specialized values into metadata dictionary.
        print("Cannot pass specialized value" + tagkey + "into metadadictionary")


# Illustrating use of getting a label given a tag here
entryID = "0010|0010"
if not metadata.HasKey(entryID):
    print("tag: " + entryID + " not found in series")
else:
    # The second parameter is mandatory in python to get the
    # string label value
    label = itk.GDCMImageIO.GetLabelFromTag(entryID, "")
    tagvalue = metadata[entryID]
    print(label[1] + " (" + entryID + ") is: " + str(tagvalue))
