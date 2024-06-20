---
name: '{{ cookiecutter.example_name }}'
---

# {{ cookiecutter.example_title }}

```{index} single: {{ cookiecutter.class_name }}
```

## Synopsis

{{ cookiecutter.example_synopsis }}

## Results

:::{figure} cthead1.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} OutputBaseline.png
:alt: Output image
:scale: 50%

Output image
:::

## Code

### Python

```{literalinclude} Code.py
:language: python
:lines: 1,16-
```

### C++

```{literalinclude} Code.cxx
:language: c++
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::{{ cookiecutter.class_name }}
```
