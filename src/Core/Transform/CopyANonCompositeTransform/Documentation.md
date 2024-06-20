---
name: CopyANonCompositeTransform
---

# Copy a Non-CompositeTransform

```{index} single: Transform pair: copy; Transform pair: clone; Transform
```

## Synopsis

Copy a non-CompositeTransform.

## Results

```none
Original transform: Euler3DTransform (0x132e880)
  RTTI typeinfo:   itk::Euler3DTransform<float>
  Reference Count: 2
  Modified Time: 5
  Debug: Off
  Object Name:
  Observers:
    none
  Matrix:
    0.930432 -0.294044 0.218711
    0.308577 0.950564 -0.0347626
    -0.197677 0.0998334 0.97517
  Offset: [3.63622, 5.66636, 5.62082]
  Center: [-3.5, -4.5, -5.5]
  Translation: [4, 5, 6]
  Inverse:
    0.930432 0.308577 -0.197677
    -0.294044 0.950564 0.0998333
    0.218711 -0.0347626 0.97517
  Singular: 0
  Euler's angles: AngleX=0.1 AngleY=0.2 AngleZ=0.3
  m_ComputeZYX = 0

Transform copy: Euler3DTransform (0x132eda0)
  RTTI typeinfo:   itk::Euler3DTransform<float>
  Reference Count: 3
  Modified Time: 10
  Debug: Off
  Object Name:
  Observers:
    none
  Matrix:
    0.930432 -0.294044 0.218711
    0.308577 0.950564 -0.0347626
    -0.197677 0.0998334 0.97517
  Offset: [3.63622, 5.66636, 5.62082]
  Center: [-3.5, -4.5, -5.5]
  Translation: [4, 5, 6]
  Inverse:
    0.930432 0.308577 -0.197677
    -0.294044 0.950564 0.0998333
    0.218711 -0.0347626 0.97517
  Singular: 0
  Euler's angles: AngleX=0.1 AngleY=0.2 AngleZ=0.3
  m_ComputeZYX = 0
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::Transform
```

```{eval-rst}
.. breathelink:: itk::CompositeTransform
```
