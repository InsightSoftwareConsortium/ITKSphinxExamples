---
name: PrintModuleLoadingPython
---

# Print ITK Python Module Loading

## Synopsis

Print how ITK Python module dependencies are lazily loaded.

## Results

Output:

```
Loading ITKPyBase... done
Loading ITKCommon... done
Loading ITKStatistics... done
Loading ITKImageFilterBase... done
Loading ITKTransform... done
Loading ITKImageFunction... done
Loading ITKImageGrid... done
Loading ITKFFT... done
Loading ITKPyUtils... done
```

## Code

### Python

```{literalinclude} Code.py
:language: python
:lines: 1, 16-
```
