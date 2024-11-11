---
name: GetListOfFacesAroundAGivenVertex
---

# Get List of Faces Around a Given Vertex

```{index} single: QuadEdgeMesh
```

## Synopsis

Get the list of faces around a given vertex.

## Results

Results:

```
79
1961
2036
1960
1
```

These faces are visualized in the figures below.

:::{figure} SelectedFaces.png
:alt: Selected faces.
:scale: 50%

The selected faces around the given vertex are highlighted in pink.
:::

```{raw} html
<div class="figure">
  <iframe src="SelectedFaces.html" width="400" height="300" seamless></iframe>
  <p class="caption">Interactive view of the selected faces</p>
</div>
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
