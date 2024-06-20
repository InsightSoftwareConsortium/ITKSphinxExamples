---
name: SmoothRGBImageUsingMinMaxCurvatureFlow
---

# Smooth RGB Image Using Min Max Curvature Flow

```{index} single: MinMaxCurvatureFlowImageFilter single: RGB pair: curvature; flow pair: min; max
```

## Synopsis

Smooth an RGB image using min/max curvature flow.

## Results

:::{figure} Gourds.png
:alt: input image
:scale: 70%

Input image.
:::

:::{figure} SmoothRGBImageUsingMinMaxCurvatureFlow.png
:scale: 70%

Output In VTK Window
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::MinMaxCurvatureFlowImageFilter
```
