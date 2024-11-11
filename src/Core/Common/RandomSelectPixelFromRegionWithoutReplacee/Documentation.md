---
name: RandomSelectPixelFromRegionWithoutReplacee
---

# Random Select Pixel From Region Without Replacing

```{index} single: ImageRandomNonRepeatingConstIteratorWithIndex pair: random; select
```

## Synopsis

Randomly select pixels from a region of an image without replacement.

## Results

Output:

```
[1, 2]
[1, 1]
[0, 2]
[2, 2]
[2, 1]
[2, 0]
[0, 0]
[0, 1]
[1, 0]
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ImageRandomNonRepeatingConstIteratorWithIndex
```
