---
name: ApplyExpNegativeImageFilter
---

# Apply Exp Negative Image Filter

```{index} single: ExpNegativeImageFilter
```

## Synopsis

Compute $exp(-K x)$ of each pixel.

## Results

:::{figure} Gourds.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} Output.png
:alt: Output image
:scale: 50%

Output image
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

### Python

```{literalinclude} Code.py
:language: python
:lines: 1, 16-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ExpNegativeImageFilter
```
