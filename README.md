# ITK Sphinx Examples

```{image} https://github.com/InsightSoftwareConsortium/ITKSphinxExamples/workflows/Build,%20test,%20publish/badge.svg?branch=master
:target: https://github.com/InsightSoftwareConsortium/ITKSphinxExamples/actions?query=workflow%3A%22Build%2C+test%2C+publish%22+branch%3Amaster
```

```{image} https://img.shields.io/badge/License-Apache%202.0-blue.svg?style=shield
:target: https://github.com/InsightSoftwareConsortium/ITKSphinxExamples/blob/master/LICENSE
```

A set of cookbook examples for the Insight Toolkit, [ITK].

## Download instructions

Clone the repository using Git:

```
$ git clone --recursive https://github.com/InsightSoftwareConsortium/ITKSphinxExamples.git
```

## Build instructions

See the [build instructions in the documentation].

## Features

### Implemented

- Stored and editable in [Git] version control.
- HTML / PDF / EPUB output.
- CTest unit testing.
- CMake ExternalData for binary data storage.
- Individual examples can be downloaded independently, and easily built/executed/hacked.
- Download the entire docs for offline viewing.
- Inline Doxygen class descriptions and links to Doxygen class documentation.
- Nightly generated Gitstats for contributors.
- Software quality dashboard.
- Index of examples that apply to given terms and classes.
- Quick search.
- Script to create a new examples from a template.
- GitHub community development.
- Selectable light/dark colorscheme.
- Online editing via GitHub.

### Todo

- See [Github Issues] for a complete list of actions to be performed, bugs, *etc.*

## Build dependencies

### Required

- [CMake] ( >= 3.16.3 )
- [ITK]  ( >= 5.3.0 )

### Optional

If building the documentation:

- [Python] ( >= 3.7 )
- [Sphinx]
- [Pandoc]
- [nbsphinx]
- [gnuplot]
- [dvipng] ( for rendered equations )
- [imagemagick]

PDF generation requires a TeX distribution like [TeX Live] or [MiKTeX].

## Development setup

Run the bash script `SetupForDevelopment.sh`:

```
$ ./Utilities/SetupForDevelopment.sh
```

[breathe]: https://github.com/michaeljones/breathe
[build instructions in the documentation]: https://itk.org/ITKExamples/Documentation/Build/index.html
[cmake]: https://cmake.org/
[dvipng]: https://sourceforge.net/projects/dvipng/
[git]: https://git-scm.com/
[github issues]: https://github.com/InsightSoftwareConsortium/ITKSphinxExamples/issues
[gnuplot]: https://www.gnuplot.info/
[imagemagick]: https://www.imagemagick.org/
[itk]: https://itk.org/
[miktex]: https://miktex.org/
[nbsphinx]: https://nbsphinx.readthedocs.io/
[pandoc]: https://pandoc.org/
[python]: https://python.org/
[sphinx]: https://sphinx-doc.org/
[tex live]: https://www.tug.org/texlive/
