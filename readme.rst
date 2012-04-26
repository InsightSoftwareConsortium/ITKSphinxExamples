ITK Examples
============

A set of cookbook examples for the Insight Toolkit, ITK_.

Download instructions
---------------------

With version of Git (>= 1.6.5)::

  $ git clone --recursive git@github.com:InsightSoftwareConsortium/ITKExamples.git


With older versions::

  $ git clone git@github.com:InsightSoftwareConsortium/ITKExamples.git
  $ cd ITKExamples
  $ git submodule update --init


Build instructions
------------------

Automatic
^^^^^^^^^

A "superbuild" is provided to automatically fetch and build everything
that is required. The procedure is almost idential to building a normal CMake
project - the only difference you must point cmake to ITKExamples/superbuild
instead of just ITKExamples::

  mkdir ~/build/ITKExamples
  cd ~/build/ITKExamples
  cmake ~/src/ITKExamples/superbuild/
  make -j2

Manual
^^^^^^

If you want to use local installations of some of the required tools, configure
and build ITKExamples as a typical CMake_ project.

Features
--------

Implemented
^^^^^^^^^^^

- Stored and editable in Git_ version control.
- HTML / PDF output.
- CTest unit testing.
- CMake ExternalData for binary data storage.
- Individual examples can be downloaded independently, and easily built/executed/hacked.
- Download the entire docs for offline viewing.

Todo
^^^^

- Anonymous online editing.
- Editable online with CodeMirror.
- Peer review with Gerrit.

- See `Github Issues`_ for a complete list of actions to be performed, bugs, *etc.*

With funding
^^^^^^^^^^^^

- Gerrit robot builds.

Build dependencies
------------------

Required
^^^^^^^^

- CMake_ ( >= 2.8.5 )
- ITK_  (>= 4.0.0 )

Optional
^^^^^^^^

If building the documentation:

- Python_ ( >= 2.7 )
- Sphinx_
- gnuplot_

Development setup
------------------

Run the bash scipt SetupForDevelopment.sh::

  $ ./utilities/SetupForDevelopment.sh

.. _Breathe: https://github.com/michaeljones/breathe
.. _CMake: http://cmake.org/
.. _Gerrit: http://code.google.com/p/gerrit/
.. _Git: http://git-scm.com/
.. _ITK: http://itk.org/
.. _Sphinx: http://sphinx.pocoo.org/
.. _Github Issues: https://github.com/InsightSoftwareConsortium/ITKExamples/issues?milestone=&labels=&state=open
.. _Python: http://python.org/
.. _gnuplot: http://www.gnuplot.info/
