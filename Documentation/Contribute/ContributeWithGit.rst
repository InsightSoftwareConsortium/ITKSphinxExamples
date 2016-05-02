.. _text-editor-submission:

Contribute with Git
===================

Clone the repository and setup for development
----------------------------------------------

The entire source tree can be downloaded with Git_:

.. code-block:: bash

  git clone --recursive https://itk.org/ITKExamples.git

After cloning the repository, it can be configured for development (confirm
proper Git configuration, setup `Git hooks`_, configure your `Gerrit Code
Review`_ account) with

.. code-block:: bash

  cd ITKExamples
  ./Utilites/SetupForDevelopment.sh


Modifying an existing example
-----------------------------

First, create a local branch::

  git checkout -b Modification


Modify existing example (source code and/or corresponding documentation).
Add files which are missing ::

  git add missing_files


Once you are done, commit your changes as follows::

  git commit -a


To submit your changes to `Gerrit Code Review`_::

  git gerrit-push


.. _CreateNewExample:

Create a new example
--------------------

To create a new example, you can make use of the Python script located in the
binary tree (/path/to/ITKExamples-build/Utilities)::

  cd /path/to/ITKExamples-build/Utilities
  ./CreateNewExample.py /path/to/source/ITK

*This script will generate cxx and rst files to be modified*

Note that the generated files are then located based on the group, module and
class name to be demonstrated. For instance an example which would demonstrate
the usage of :itkdox:`itk::Image` will be generated in
``src/Core/Common/``.

Please do not add images directly to the repository.  Instead, use the
:ref:`content link system <upload-binary-data>`.


.. _Git: http://git-scm.com/
.. _Git hooks: http://git-scm.com/book/en/Customizing-Git-Git-Hooks
.. _Gerrit Code Review: http://review.source.kitware.com/#/q/project:ITKExamples,n,z
