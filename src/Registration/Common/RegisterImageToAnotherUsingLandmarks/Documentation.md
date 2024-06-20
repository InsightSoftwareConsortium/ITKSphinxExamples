---
name: RegisterImageToAnotherUsingLandmarks
---

# Register Image to Another Using Landmarks

```{index} single: LandmarkBasedTransformInitializer single: landmark
```

## Synopsis

Rigidly register one image to another using manually specified landmarks.

## Results

:::{figure} fixed.png
:alt: fixed.png
:scale: 70%

fixed.png
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

## Code

### Python

```{literalinclude} Code.py
:language: python
:lines: 1, 20-
```

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::LandmarkBasedTransformInitializer
```
