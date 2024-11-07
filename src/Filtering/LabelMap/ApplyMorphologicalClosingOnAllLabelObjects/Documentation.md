---
name: ApplyMorphologicalClosingOnAllLabelObjects
---

# Apply Morphological Closing on All Label Objects

```{index} single: ObjectByObjectLabelMapFilter single: LabelUniqueLabelMapFilter
```

## Synopsis

Apply morphological closing operation on all LabelObjects of a given LabelMap.

In details:

- read image is converted to LabelMap
- apply morphological closing operation on all LabelObjects of the LabelMap
- make sure there is no overlapping LabelObject with using LabelUniqueLabelMapFilter
- convert the LabelMap to LabelImage
- write the corresponding LabelImage

## Results

:::{figure} 2th_cthead1.png
:alt: Input image
:scale: 50%

Input image
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
.. breathelink:: itk::ObjectByObjectLabelMapFilter
```

```{eval-rst}
.. breathelink:: itk::LabelUniqueLabelMapFilter
```
