---
name: ClusterPixelsInGrayscaleImage
---

# Cluster Pixels in Grayscale Image

```{index} single: ScalarImageKmeansImageFilter pair: grayscale; image
```

## Synopsis

Cluster the pixels in a greyscale image.

## Results

:::{figure} ClusterPixelsInGrayscaleImage.png
:alt: VTK Window
:scale: 70%

Output In VTK Window
:::

Output:

```
cluster[0]     estimated mean : 10
cluster[1]     estimated mean : 100
cluster[2]     estimated mean : 200
Number of pixels per class
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ScalarImageKmeansImageFilter
```
