---
name: GlobalRegistrationOfTwoImages
---

# Global Registration of Two Images

```{index} single: ImageRegistrationMethod single: TranslationTransform
```

## Synopsis

A basic global registration of two images.

## Results

:::{figure} fixed.png
:alt: fixing.png
:scale: 70%

fixing.png
:::

:::{figure} moving.png
:alt: moving.png
:scale: 70%

moving.png
:::

:::{figure} output.png
:alt: output.png
:scale: 70%

output.png
:::

Output:

```
Result =
Translation X = 15.0103
Translation Y = -1.12679
Iterations    = 15
Metric value  = 2374.3
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ImageRegistrationMethod
```

```{eval-rst}
.. breathelink:: itk::TranslationTransform
```
