---
name: AddPointsAndEdges
---

# Add Points and Edges

```{index} single: Mesh pair: points; edges
```

## Synopsis

How to add points and edges to a mesh.

## Results

Output:

```
Points = 4
[-1, -1, 0]
[1, -1, 0]
[1, 1, 0]
[1, 1, 1]
line first point id: 2
line second point id: 3
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::Mesh
```
