---
name: AddConstantToPixelsWithoutDuplicatingImage
---

# Add Constant to Every Pixel Without Duplicating Memory

```{index} single: AddPixelAccessor
```

## Synopsis

Add a constant to every pixel without duplicating the image in memory (an accessor).

## Results

Output:

```
addPixelAccessor.SetValue(5)
image->GetPixel[0, 0]: 20 adaptor->GetPixel[0, 0]: 25
addPixelAccessor.SetValue(100)
image->GetPixel[0, 0]: 20 adaptor->GetPixel[0, 0]: 120
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::Accessor::AddPixelAccessor
```
