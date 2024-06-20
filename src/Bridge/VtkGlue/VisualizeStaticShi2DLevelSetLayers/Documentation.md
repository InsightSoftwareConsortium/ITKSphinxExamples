---
name: VisualizeStaticShi2DLevelSetLayers
---

# Visualize a Static Sparse Shi 2D Level-Set Layers

```{index} single: vtkVisualize2DSparseLevelSetLayers single: BinaryImageToLevelSetImageAdaptor single: ShiSparseLevelSetImage
```

## Synopsis

Visualize a static sparse Shi level-set function 2D's layers. From the input
image, first an otsu thresholding technique is used to get a binary mask, which
is then converted to a sparse level-set function.

Note that Shi's representation is composed of 4 layers (values = {-3, -1, +1, +3})

## Results

:::{figure} cells.png
:alt: Input image (cells)
:scale: 100%

Input image
:::

:::{figure} levelsets.png
:alt: Static level-sets zero-sets
:scale: 100%

Static level-sets
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

% [breathelink:: itk::VTKVisualize2DSparseLevelSetLayers]
