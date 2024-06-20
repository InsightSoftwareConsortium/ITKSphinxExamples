---
name: ComputePlanarParameterizationOfAMesh
---

# Compute Planar Parameterization of a Mesh

```{index} single: ParameterizationQuadEdgeMeshFilter
```

## Synopsis

Compute planar parameterization of a surface mesh represented by one itk::QuadEdgeMesh.

## Results

:::{figure} InputMesh.png
:alt: Input mesh
:scale: 100%

Input mesh
:::

:::{figure} OutputMeshes.png
:alt: Output meshes
:scale: 100%

Output planes with left column) SQUARE, and right column) DISK BorderType,
and row 1) OnesMatrix, 2) InverseEuclideanMatrix 3) ConformalMatrix, 4)
AuthalicMatrix, and 5) HarmonicMatrix CoefficientType.
:::

```{raw} html
<div class="figure">
  <iframe src="mushroom.html" width="400" height="300" seamless></iframe>
  <p class="caption">Interactive input mesh</p>
</div>

<div class="figure">
  <iframe src="param_border0_coeff0.html" width="400" height="300" seamless></iframe>
  <p class="caption">Interactive SQUARE BorderType, OnesMatrix CoefficientType output</p>
</div>

<div class="figure">
  <iframe src="param_border1_coeff0.html" width="400" height="300" seamless></iframe>
  <p class="caption">Interactive DISK BorderType, OnesMatrix CoefficientType output</p>
</div>
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ParameterizationQuadEdgeMeshFilter
```
