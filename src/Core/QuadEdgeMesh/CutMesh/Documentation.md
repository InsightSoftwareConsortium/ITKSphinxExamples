---
name: CutMesh
---

# Cut Mesh

```{index} single: QuadEdgeMesh single: QuadEdgeMeshPolygonCell single: MeshFileReader single: MeshFileWriter pair: QuadEdge; GetLnext pair: QuadEdge; GetOnext pair: QuadEdgeMeshPoint; CastFrom pair: QuadEdgeMeshPolygonCell; GetEdgeRingEntry pair: QuadEdgeMesh; AddPoint pair: QuadEdgeMesh; AddFaceTriangle pair: PointSet; GetPoints
```

## Synopsis

Given a bounding box and a mesh, first retrieve all vertices whose coordinates
are in the bounding box; then retrieve all faces connected to these vertices.

## Results

:::{figure} inputMesh.png
:alt: Input mesh
:scale: 50%

Input mesh
:::

:::{figure} outputMesh.png
:alt: Output mesh
:scale: 50%

Output mesh (cut)
:::

```{raw} html
<div class="figure">
  <iframe src="genusZeroSurface01.html" width="200" height="225" seamless></iframe>
  <p class="caption">Interactive input mesh</p>
</div>

<div class="figure">
  <iframe src="CutMeshOutput.html" width="200" height="225" seamless></iframe>
  <p class="caption">Interactive cut output mesh</p>
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
