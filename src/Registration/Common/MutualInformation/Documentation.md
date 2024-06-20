---
name: MutualInformation
---

# Mutual Information

```{index} single: MutualInformationImageToImageMetric single: TranslationTransform
```

```{toctree}
:maxdepth: 1

MutualInformation.ipynb
```

## Synopsis

Global registration by maximizing the mutual information and using a translation only transform.

## Results

:::{figure} fixed.png
:alt: fixed.png
:scale: 70%

fixed.png
:::

:::{figure} moving.png
:alt: moving.png
:scale: 70%

moving.png
:::

:::{figure} OutputBaseline.png
:alt: OutputBaseline.png
:scale: 70%

OutputBaseline.png
:::

Output:

```
Optimizer stop condition: GradientDescentOptimizer: Maximum number of iterations (200) exceeded.

  Result =
   Translation X = 12.9484
   Translation Y = 17.0856
   Iterations    = 200
   Metric value  = 0.594482
   Numb. Samples = 567
```

## Jupyter Notebook

```{image} https://mybinder.org/badge_logo.svg
:target: https://mybinder.org/v2/gh/InsightSoftwareConsortium/ITKSphinxExamples/master?filepath=src%2FRegistration%2FCommon%2FMutualInformation%2FMutualInformation.ipynb
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::MutualInformationImageToImageMetric
```

```{eval-rst}
.. breathelink:: itk::TranslationTransform
```
