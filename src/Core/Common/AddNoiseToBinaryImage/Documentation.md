---
name: AddNoiseToBinaryImage
---

# Add Noise To Binary Image

```{index} single: ImageRandomNonRepeatingIteratorWithIndex single: noise pair: binary; image
```

## Synopsis

Add noise to a binary image.

## Results

:::{figure} Yinyang.png
:alt: Input.png
:scale: 70%

Yinyang.png
:::

:::{figure} AddNoiseToBinaryImage.png
:alt: Output.png
:scale: 70%

Output.png
:::

Output:

```
Number of random samples: 105062
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ImageRandomNonRepeatingIteratorWithIndex
```
