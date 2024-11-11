---
name: CreateAnImageOfVectors
---

# Create an Image of Vectors

```{index} single: Vector single: Image
```

## Synopsis

This example illustrates how to instantiate and use an *itk::Image* whose pixels are of *itk::Vector* type.

## Results

```
C++

[1.345, 6.841, 3.295]

Python

itkVectorF3 ([1.345, 6.841, 3.295])
```

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
.. breathelink:: itk::Vector
```

```{eval-rst}
.. breathelink:: itk::Image
```
