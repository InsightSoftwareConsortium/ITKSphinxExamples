ITK Examples
============

A set of cookbook examples for the Insight Toolkit, ITK_.


Build instructions
------------------

Automatic:
A "superbuild" is provided to automatically fetch and build everything
that is required. The procedure is almost idential to building a normal CMake
project - the only difference you must point cmake to ITKExamples/superbuild
instead of just ITKExamples::

 mkdir ~/build/ITKExamples
 cd ~/build/ITKExamples
 cmake ~/src/ITKExamples/superbuild/

Manual:

If you want to use local installations of some of the required tools, configure
and build ITKExamples as a typical CMake_ project.

.. _Breathe: https://github.com/michaeljones/breathe
.. _CMake: http://cmake.org/
.. _Gerrit: http://code.google.com/p/gerrit/
.. _Git: http://git-scm.com/
.. _ITK: http://itk.org/
.. _Sphinx: http://sphinx.pocoo.org/


Features
--------

Implemented
^^^^^^^^^^^

- Stored and editable in Git_ version control.
- HTML output.
- CTest unit testing.
- CMake ExternalData for binary data storage.
- Individual examples can be downloaded independently, and easily built/executed/hacked.

Todo
^^^^

- LaTeX-based PDF output.
- Text output.
- Download the entire docs for offline viewing.
- Anonymous online editing.
- Editable online with CodeMirror.
- Peer review with Gerrit.
- Reciprical Doxygen integration with breathe + automatic injection of the
  example into the class doc.  This also used for search enhancement and
  categorization.
- CDash dashboard.

With funding
^^^^^^^^^^^^

- Gerrit robot builds.

Build dependencies
------------------

Required
^^^^^^^^

- CMake_
- ITK_

Optional
^^^^^^^^

If building the documentation:

- Breathe_
- Sphinx_
