---
name: KeepBinaryRegionsThatMeetSpecific
---

# Keep Binary Regions That Meet Specific Properties

```{index} single: BinaryStatisticsOpeningImageFilter single: binary pair: binary; property pair: threshold; property
```

## Synopsis

Keep only regions that meet a specified threshold of a specified property.

## Results

:::{figure} input.png
:alt: input.mhd
:scale: 70%

input.mhd
:::

:::{figure} output.png
:alt: output.mhd
:scale: 70%

output.mhd
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::BinaryStatisticsOpeningImageFilter
```
