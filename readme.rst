ITK Examples
============

A set of cookbook examples for the Insight Toolkit, ITK_.


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

- Sphinx_ (build the documentation)


Build instructions
------------------

Configure and build as a typical CMake_ project.

.. _CMake: http://cmake.org/
.. _Gerrit: http://code.google.com/p/gerrit/
.. _Git: http://git-scm.com/
.. _ITK: http://itk.org/
.. _Sphinx: http://sphinx.pocoo.org/

