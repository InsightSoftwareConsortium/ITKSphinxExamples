---
name: KeepRegionsAboveLevel
---

# Keep Regions Above Certain Level

```{index} single: LabelShapeKeepNObjectsImageFilter single: region pair: level; property
```

## Synopsis

Keep only regions that rank above a certain level of a particular property.

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
.. breathelink:: itk::LabelShapeKeepNObjectsImageFilter
```
