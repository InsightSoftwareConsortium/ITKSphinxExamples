---
name: ReadMesh
---

# Read Mesh

```{index} single: MeshFileReader single: Mesh pair: Mesh; GetPoint pair: Point; EuclideanDistanceTo
```

## Synopsis

Read a mesh and display the Euclidean distance in between 2 given vertices

## Results

:::{figure} InputMesh.png
:alt: Input mesh
:scale: 50%

Input mesh
:::

```{raw} html
<div class="figure">
  <iframe src="InputMesh.html" width="200" height="225" seamless></iframe>
  <p class="caption">Interactive input mesh</p>
</div>
```

Distance:

```
0.604093
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::MeshFileReader
```
