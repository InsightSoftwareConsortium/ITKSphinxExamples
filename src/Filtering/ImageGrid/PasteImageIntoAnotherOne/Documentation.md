---
name: PasteImageIntoAnotherOne
---

# Paste Image Into Another One

```{index} single: PasteImageFilter
```

## Synopsis

Paste one itk::Image into another one

## Results

:::{figure} Yinyang.png
:alt: Source image
:scale: 50%

Source image
:::

:::{figure} Gourds.png
:alt: Destination image
:scale: 50%

Destination image
:::

:::{figure} OutputBaseline.png
:alt: Output image
:scale: 50%

Output image
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::PasteImageFilter
```
