---
name: CalculateAreaAndVolumeOfSimplexMesh
---

# Calculate Area and Volume of Simplex Mesh

```{index} single: SimplexMeshVolumeCalculator pair: area; volume
```

## Synopsis

Calculate the area and volume of an itk::SimplexMesh.

## Results

Output:

```
Ideal Volume: 523.599
Mesh Volume: 520.812
Ideal Surface Area: 314.159
Mesh Surface Area: 313.1
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::SimplexMeshVolumeCalculator
```
