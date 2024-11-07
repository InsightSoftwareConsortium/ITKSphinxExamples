---
name: ConvertTriangleMeshToBinaryImage
---

# Convert Triangle Mesh to Binary Image

```{index} single: TriangleMeshToBinaryImageFilter
```

## Synopsis

Convert a triangular itk::Mesh to binary itk::Image

## Results

:::{figure} ConvertTriangleMeshToBinaryImageInputs.png
:alt: Input image and mesh
:scale: 80%

Input 3D Image and Mesh
:::

:::{figure} Output.png
:alt: Output image
:scale: 100%

Output image
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::TriangleMeshToBinaryImageFilter
```
