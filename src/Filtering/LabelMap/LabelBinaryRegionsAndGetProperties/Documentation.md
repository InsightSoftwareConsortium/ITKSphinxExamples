---
name: LabelBinaryRegionsAndGetProperties
---

# Label Binary Regions and Get Properties

```{index} single: BinaryImageToShapeLabelMapFilter pair: binary; regions pair: label; binary pair: label; properties
```

## Synopsis

Label binary regions in an image and get their properties.

## Results

:::{figure} image.png
:alt: image.png
:scale: 70%

image.png
:::

Output:

```
There are 1 objects.
Object 0 has bounding box ImageRegion (0x7ff924a4e558)
Dimension: 2
Index: [6, 6]
Size: [4, 4]
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::BinaryImageToShapeLabelMapFilter
```
