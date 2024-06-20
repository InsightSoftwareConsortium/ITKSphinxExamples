---
name: ExtractGivenLabelObject
---

# Extract Given Label Object

```{index} single: LabelSelectionLabelMapFilter
```

## Synopsis

Extract one given LabelObject from one LabelMap into a new LabelMap and remaining ones into another one.

## Results

:::{figure} 2th_cthead1.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} Output1Baseline.png
:alt: Output1 image
:scale: 50%

first output (i.e. LabelMap with the LabelObject of interest)
:::

:::{figure} Output2Baseline.png
:alt: Output2 image
:scale: 50%

second output (i.e. LabelMap with remaining LabelObjects)
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::LabelSelectionLabelMapFilter
```
