==========
Contribute
==========

The ITK Examples are stored in the Git_ distributed version control system, and
the mainline repository can be found at ITKExamplesRepo_.  Files
in the repository can be edited either with the `web interface`_ or the typical
`text editor / version control workflow`_ used when modifying source code.

Examples code can be written in the C++, Python, or Java programming languages.
Documentation for the examples is writted in reStructuredText_ / Sphinx_.  A
Sphinx is a build system that uses the reStructuredText syntax with additional
capabilies such as multi-document projects and rendering of LaTeX-style
equations.  A good reference for the easy-to-learn reStructuredText syntax is
the `Quick reStructuredText`_ guide.

.. _`web interface`:

Contribute with the web interface
=================================


Modifying an existing example
-----------------------------

Todo.

Create a new example
--------------------

Todo.

.. _`text editor / version control workflow`:

Contribute with Git
===================

Modifying an existing example
-----------------------------

Todo.

Create a new example
--------------------

Todo.

Contribute a nightly build
==========================

Nightly build
-------------

Examples are nightly compiled, ran and compared to baseline images to ensure
these examples remain valid on all supported platforms, and to ensure changes
in the development of ITK do not alterate these examples. Following the same
principle, the documentation is generated nightly.

Warnings, errors and any other potential issues are reported on the Dashboard_.

Contribute
----------

On Windows
++++++++++

Todo.

On Mac/Linux
++++++++++++

`Set-up a cron-job`_ nightly any time after ?? with the following command to be ran:

  ctest -S /path/to/ITKExamples/scripts/itkexamples_common.cmake -A -V

Peer review with Gerrit
=======================

Todo.

.. todo:: replace with http://itk.org/ITKExamples/
.. _ITKExamplesRepo:        http://mmmccormick.com/ITKExamples
.. _Git:                    http://git-scm.com/
.. _reStructuredText:       http://docutils.sourceforge.net/rst.html
.. _Sphinx:                 http://sphinx.pocoo.org/
.. _Quick reStructuredText: http://docutils.sourceforge.net/docs/user/rst/quickref.html
.. _Dashboard:              http://mmmccormick.com/CDash/index.php?project=ITKExamples
.. _Set-up a cron-job:      http://en.wikipedia.org/wiki/Cron 
