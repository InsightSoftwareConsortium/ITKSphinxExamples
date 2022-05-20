import itk
import argparse

parser = argparse.ArgumentParser(description="Filtering Of An Image with DiscreteGaussianFilter")
parser.add_argument("input_image")
parser.add_argument("variance", type=float)
args = parser.parse_args()

PixelType = itk.F

# Read Image in float data type
inputImage = itk.imread(args.input_image, PixelType)

# Check some information from the inputImage
print('Shape ', inputImage.shape)
print('dtype is ', inputImage.dtype)
print('type is ', type(inputImage))

variance = args.variance
filteredImage = itk.discrete_gaussian_image_filter(inputImage, variance=variance)

# Check some information from the filteredImage
print('Shape ', filteredImage.shape)
print('dtype is ', filteredImage.dtype)
print('type is ', type(filteredImage))

# Visualize the result using matplotlib
import matplotlib.pyplot as plt
plt.imshow(filteredImage)
plt.show()
