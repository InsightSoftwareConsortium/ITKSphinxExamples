---
name: ConvertFileFormats
---

# Convert File Formats

```{index} single: ImageFileReader, ImageFileWriter
```

## Synopsis

Convert from one image file format to another.  ITK will automatically detect
the file type of the input and output files by their extension, and an
`itk::ImageFileReader` and `itk::ImageFileWriter` will use the appropriate
`ImageIO` class.

## Results

:::{figure} Gourds.png
:alt: Gourds.png
:scale: 50%

Gourds.png
:::

:::{figure} OutputBaseline.jpg
:alt: Gourds.jpg
:scale: 50%

Gourds.jpg
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ImageFileReader itk::ImageFileWriter
```
