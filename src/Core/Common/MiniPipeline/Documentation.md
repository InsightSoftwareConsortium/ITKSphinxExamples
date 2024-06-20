---
name: MiniPipeline
---

# Mini Pipeline

```{index} single: Image
```

## Synopsis

Mini Pipeline.

## Results

Output:

```
Input:
ImageRegion (0x7fe4c3aaadb0)
Dimension: 2
Index: [0, 0]
Size: [200, 300]

Input:
ImageRegion (0x7fe4c3aab920)
Dimension: 2
Index: [0, 0]
Size: [200, 300]
```

:::{figure} MiniPipelineOutput.png
:alt: Output.png
:scale: 70%

Output.png
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::Image
```
