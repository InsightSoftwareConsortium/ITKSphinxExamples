---
name: MakeOutOfBoundsPixelsReturnConstValue
---

# Make Out of Bounds Pixels Return Constant Value

```{index} single: ConstantBoundaryCondition pair: pixel; constant
```

## Synopsis

Make out of bounds pixels return a constant value.

## Results

:::{figure} MakeOutOfBoundsPixelsReturnConstValue.png
:alt: VTK Window
:scale: 70%

Output In VTK Window
:::

Output:

```
Index: [-1, -1] Pixel: 0 = 0
Index: [0, -1] Pixel: 1 = 0
Index: [1, -1] Pixel: 2 = 0
Index: [-1, 0] Pixel: 3 = 0
Index: [0, 0] Pixel: 4 = 255
Index: [1, 0] Pixel: 5 = 255
Index: [-1, 1] Pixel: 6 = 0
Index: [0, 1] Pixel: 7 = 255
Index: [1, 1] Pixel: 8 = 255
Index: [0, -1] Pixel: 0 = 0
Index: [1, -1] Pixel: 1 = 0
Index: [2, -1] Pixel: 2 = 0
Index: [0, 0] Pixel: 3 = 255
Index: [1, 0] Pixel: 4 = 255
Index: [2, 0] Pixel: 5 = 255
Index: [0, 1] Pixel: 6 = 255
Index: [1, 1] Pixel: 7 = 255
Index: [2, 1] Pixel: 8 = 255
Index: [1, -1] Pixel: 0 = 0
Index: [2, -1] Pixel: 1 = 0
Index: [3, -1] Pixel: 2 = 0
Index: [1, 0] Pixel: 3 = 255
Index: [2, 0] Pixel: 4 = 255
Index: [3, 0] Pixel: 5 = 255
Index: [1, 1] Pixel: 6 = 255
Index: [2, 1] Pixel: 7 = 255
Index: [3, 1] Pixel: 8 = 255
Index: [2, -1] Pixel: 0 = 0
Index: [3, -1] Pixel: 1 = 0
Index: [4, -1] Pixel: 2 = 0
Index: [2, 0] Pixel: 3 = 255
Index: [3, 0] Pixel: 4 = 255
Index: [4, 0] Pixel: 5 = 255
Index: [2, 1] Pixel: 6 = 255
Index: [3, 1] Pixel: 7 = 255
Index: [4, 1] Pixel: 8 = 255
Index: [3, -1] Pixel: 0 = 0
Index: [4, -1] Pixel: 1 = 0
Index: [5, -1] Pixel: 2 = 0
Index: [3, 0] Pixel: 3 = 255
Index: [4, 0] Pixel: 4 = 255
Index: [5, 0] Pixel: 5 = 0
Index: [3, 1] Pixel: 6 = 255
Index: [4, 1] Pixel: 7 = 255
Index: [5, 1] Pixel: 8 = 0
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ConstantBoundaryCondition
```
