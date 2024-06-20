---
name: TraceMemoryBetweenPoints
---

# Trace Memory Between Points

```{index} single: MemoryProbe
```

## Synopsis

Trace the memory charge between the execution of two pieces of code.  Note that
the memory must be used for it to be counted.

## Results

Results:

```
We are measuring Memory in units of kB.

** Start **
Mean: 0
Total: 0

** After allocation **
Mean: 1056
Total: 2112

** After deallocation **
Mean: 60
Total: 180
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::MemoryProbe
```
