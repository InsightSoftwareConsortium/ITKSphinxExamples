---
name: OverlayLabelMapOnTopOfAnImage
---

# Overlay Label Map on Top of an Image

```{index} single: LabelMapOverlayImageFilter
```

## Synopsis

Apply a colormap to a label map and superimpose it on an image

## Results

:::{figure} Gourds.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} label.png
:alt: Label map
:scale: 50%

Label image
:::

:::{figure} OutputBaseline.png
:alt: Output image
:scale: 50%

Output image
:::

## Code

### Python

```{literalinclude} Code.py
:language: python
:lines: 1, 16-
```

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::LabelMapOverlayImageFilter
```
