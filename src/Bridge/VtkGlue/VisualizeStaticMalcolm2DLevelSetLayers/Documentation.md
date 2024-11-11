---
name: VisualizeStaticMalcolm2DLevelSetLayers
---

# Visualize a Static Sparse Malcolm 2D Level-Set Layers

```{index} single: vtkVisualize2DSparseLevelSetLayers single: BinaryImageToLevelSetImageAdaptor single: MalcolmSparseLevelSetImage
```

## Synopsis

Visualize a static sparse Malcolm level-set function 2D's layers. From the input
image, first an otsu thresholding technique is used to get a binary mask, which
is then converted to a sparse level-set function.

Note that Malcolm's representation is composed of a single layer (value = \{0});

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
