#!/usr/bin/env python
import itk
import sys

if len(sys.argv) != 5:
    print("Usage: " + sys.argv[0] + "< Input Image > < Output Image > [Mean] [Standard Deviation]")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
mean = float(sys.argv[3])
deviation = float(sys.argv[4])

# Unsigned Char for png usage
InputPixelType = itk.UC
OutputPixelType = itk.UC
Dimension = 2

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

ReaderType = itk.ImageFileReader[InputImageType]
reader = ReaderType.New()
reader.SetFileName(inputImage)

FilterType = itk.AdditiveGaussianNoiseImageFilter[InputImageType, InputImageType]
AdditiveFilter = FilterType.New()
AdditiveFilter.SetInput(reader.GetOutput())
AdditiveFilter.SetMean(mean)
AdditiveFilter.SetStandardDeviation(deviation)



WriterType = itk.ImageFileWriter[OutputImageType]
writer = WriterType.New()
writer.SetFileName(outputImage)
writer.SetInput(AdditiveFilter.GetOutput())

writer.Update()
