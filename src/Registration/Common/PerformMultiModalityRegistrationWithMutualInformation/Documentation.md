---
name: PerformMultiModalityRegistrationWithMutualInformation
---

# Perform Multi Modality Registration With Viola Wells Mutual Information

```{index} single: MutualInformationImageToImageMetric, GradientDescentOptimizer single: RegularStepGradientDescentOptimizer, NormalizeImageFilter single: DiscreteGaussianImageFilter, Command pair: registration; multi-modality pair: MutualInformationImageToImageMetric; SetNumberOfSpatialSamples
```

## Synopsis

Rigid registration between two modalities with a Viola-Wells like mutual information metric.

## Results

:::{figure} PerformMultiModalityRegistrationWithMutualInformationInputImagesFigure.png
:alt: Input images

Input fixed image (left) and moving image (right);
:::

:::{figure} OutputBaseline.png
:alt: Output image

Output registered image.
:::

:::{figure} PerformMultiModalityRegistrationWithMutualInformationCheckerboardsFigure.png
:alt: Checkerboards before and after.

Fixed/moving image checkerboard before (left) and after (right).
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::MutualInformationImageToImageMetric
```
