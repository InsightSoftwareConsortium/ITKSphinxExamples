---
name: IterateRegionWithAccessToIndexWithoutWriteAccess
---

# Iterate Region in Image With Access to Index Without Write Access

```{index} single: ImageRegionConstIteratorWithIndex pair: write; access single: index
```

## Synopsis

Iterate over a region of an image with efficient access to the current index (without write access).

## Results

:::{figure} Yinyang.png
:scale: 70%

Yinyang.png
:::

:::{figure} IterateRegionWithAccessToIndexWithoutWriteAccess.png
:scale: 70%

Yinyang.png In VTK Window
:::

Output:

```
An extensive list of the neighborhood will be printed to the screen.
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ImageRegionConstIteratorWithIndex
```
