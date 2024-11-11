---
name: BlurringAnImageUsingABinomialKernel
---

# Blurring an Image Using a Binomial Kernel

```{index} single: BinomialBlurImageFilter
```

## Synopsis

The BinomialBlurImageFilter computes a nearest neighbor average
along each dimension. The process is repeated a number of times, as
specified by the user. In principle, after a large number of iterations
the result will approach the convolution with a Gaussian.

## Results

% figure::cthead1.png
% :scale: 50%
% :alt: Input image
%
% Input image

% figure::OutputBaseline.png
% :scale: 50%
% :alt: Output image
%
% Output image

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
.. breathelink:: itk::BinomialBlurImageFilter
```
