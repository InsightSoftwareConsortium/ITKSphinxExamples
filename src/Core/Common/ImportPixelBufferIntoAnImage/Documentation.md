---
name: ImportPixelBufferIntoAnImage
---

# Import Pixel Buffer Into an Image

```{index} single: ImportImageFilter
```

## Synopsis

This example illustrates how to import data into an `Image`
class. This is particularly useful for interfacing with other software
systems. Many systems use a contiguous block of memory as a buffer
for image pixel data. The current example assumes this is the case and
feeds the buffer into an `ImportImageFilter`, thereby producing an
image as output.

Here we create a synthetic image with a centered sphere in
a locally allocated buffer and pass this block of memory to the
`ImportImageFilter`. This example is set up so that on execution, the
user must provide the name of an output file as a command-line argument.

## Results

:::{figure} OutputBaseline.png
:alt: Output image
:scale: 50%

Output image
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ImportImageFilter
```
