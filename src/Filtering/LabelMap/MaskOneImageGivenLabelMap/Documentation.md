---
name: MaskOneImageGivenLabelMap
---

# Mask One Image Given Label Map

```{index} single: LabelMapMaskImageFilter
```

## Synopsis

Mask the content of one input itk::Image according to one input itk::LabelMap

## Results

:::{figure} cthead1.png
:alt: Input image
:scale: 100%

Input image
:::

:::{figure} 2th_cthead1.png
:alt: Input label image
:scale: 100%

Input label image
:::

:::{figure} Output1Baseline.png
:alt: Masked output 1
:scale: 100%

Masked output with label 100, background 0.
:::

:::{figure} Output2Baseline.png
:alt: Masked output 2
:scale: 100%

Masked output with label 0, background 0, negated, cropped, and border size
10\.
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::LabelMapMaskImageFilter
```
