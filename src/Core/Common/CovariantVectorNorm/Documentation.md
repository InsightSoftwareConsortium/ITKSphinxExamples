---
name: CovariantVectorNorm
---

# Covariant Vector Norm

```{index} single: CovariantVector pair: CovariantVector; GetNorm pair: CovariantVector; GetSquaredNorm pair: CovariantVector; Normalize
```

## Synopsis

Compute the norm of a CovariantVector and normalize it.

## Results

Output:

```
v: [1, 2, 3]
vnorm: 3.74166
vnorm2: 14
v: [0.267261, 0.534522, 0.801784]
u: [0.267261, 0.534522, 0.801784]
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
