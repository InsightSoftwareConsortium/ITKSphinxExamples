---
name: KeepRegionsThatMeetSpecific
---

# Keep Regions That Meet Specific Properties

```{index} single: ShapeOpeningLabelMapFilter single: region pair: threshold; property
```

## Synopsis

Keep only regions that meet a specified threshold of a specified property.

## Results

:::{figure} input.png
:alt: input.png
:scale: 70%

input.png
:::

:::{figure} output.png
:alt: output.png
:scale: 70%

output.png
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ShapeOpeningLabelMapFilter
```
