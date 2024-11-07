---
name: ExtractIsoSurface
---

# Extract Iso Surface

```{index} single: BinaryMask3DMeshSource
```

## Synopsis

Extract the iso surface as one itk::Mesh from a 3D itk::Image

## Results

:::{figure} MeshAndVolume.png
:alt: Input image and resulting mesh
:scale: 50%

Input 3D image with iso-surface mesh
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::BinaryMask3DMeshSource
```
