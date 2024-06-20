---
name: ComputeHistogramFromGrayscaleImage
---

# Compute Histogram From Grayscale Image

```{index} single: ImageToHistogramFilter
```

## Synopsis

Compute a histogram from a grayscale image

## Results

:::{figure} sf4.png
:alt: Input grayscale image.
:scale: 100%

Input grayscale image.
:::

Output:

```
Frequency = [ 0,
8593,
17734,
11515,
5974,
2225,
2400,
3422,
3531,
3283,
2125,
2628,
1954,
152,
0,
0 ]
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::Statistics::ImageToHistogramFilter
```
