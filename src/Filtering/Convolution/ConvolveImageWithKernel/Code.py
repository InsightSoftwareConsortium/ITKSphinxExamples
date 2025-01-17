import itk
import numpy as np
import argparse

parser = argparse.ArgumentParser(description="Convolve Image With Kernel")
parser.add_argument("input_image")
parser.add_argument("width", type=int)
args = parser.parse_args()

PixelType = itk.F

# Read Image in float data type
inputImage = itk.imread(args.input_image, PixelType)

width = 10
if args.width:
    width = args.width


def CreateSmoothKernel(width):
    return np.ones([width, width], "float32") / (width * width)


kernel = CreateSmoothKernel(width)
kernel_image = itk.image_from_array(kernel)

# Convolve image with kernel.
filteredImage = itk.convolution_image_filter(inputImage, kernel_image=kernel_image)

# Write the output Image
itk.imwrite("ConvolveImageWithKernelPython.png", filteredImage)

# Visualize the result using matplotlib
import matplotlib.pyplot as plt

plot_image = np.concatenate((inputImage, filteredImage), axis=1)
plt.imshow(plot_image)
plt.title("Visualize using Matplotlib, Kernel width = " + str(width))
plt.show(block=False)
plt.pause(3)
plt.close()
