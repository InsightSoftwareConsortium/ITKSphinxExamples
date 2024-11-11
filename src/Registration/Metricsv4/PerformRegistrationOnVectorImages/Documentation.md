---
name: PerformRegistrationOnVectorImages
substitutions:
  fixedImage: |-
    ```{image} orange.jpg
    :alt: Fixed image.
    :scale: 50%
    ```
  fixedImageCaption: Fixed image.
  movingImage: |-
    ```{image} apple.jpg
    :alt: Moving image.
    :scale: 50%
    ```
  movingImageCaption: Moving image.
  resampledMovingImage: |-
    ```{image} OutputBaseline.jpg
    :alt: Resampled moving image.
    :scale: 50%
    ```
  resampledMovingImageCaption: Resampled, registered moving image.
---

# Perform Registration on Vector Images

```{index} single: VectorImageToImageMetricTraitsv4
```

## Synopsis

Register images that have multi-component pixels like an itk::VectorImage or
an itk::Image\< itk::Vector, Dimension >.

## Results

```{eval-rst}
+---------------------+----------------------+-------------------------------+
|     |fixedImage|    |     |movingImage|    |      |resampledMovingImage|   |
+                     +                      +                               +
| |fixedImageCaption| | |movingImageCaption| | |resampledMovingImageCaption| |
+---------------------+----------------------+-------------------------------+
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::VectorImageToImageMetricTraitsv4
```
