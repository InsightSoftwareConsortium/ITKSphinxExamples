---
name: CovariantVectorDotProduct
---

# Covariant Vector Dot Product

```{index} single: CovariantVector pair: CovariantVector; operator *
```

## Synopsis

Dot product of CovariantVectors

## Results

Output:

```
u :[-1, 1, -1]
v :[1, 2, 3]
DotProduct( u, v ) = -2
u - DotProduct( u, v ) * v = [1, 5, 5]
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::CovariantVector
```
