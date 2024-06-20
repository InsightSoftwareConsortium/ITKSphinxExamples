---
name: PrintVertexNeighbors
---

# Print Vertex Neighbors

```{index} single: QuadEdgeMesh
```

## Synopsis

Print the neighbors of a given vertex.

## Results

:::{figure} InputMesh.png
:alt: Input mesh
:scale: 50%

Input mesh
:::

```{raw} html
<div class="figure">
  <iframe src="InputMesh.html" width="400" height="300" seamless></iframe>
  <p class="caption">Interactive input mesh</p>
</div>
```

Example output:

```
3435
6999
5422
2869
244
584
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::QuadEdgeMesh
```
