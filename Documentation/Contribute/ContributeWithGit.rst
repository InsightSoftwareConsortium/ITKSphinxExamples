.. _text-editor-submission:

Contribute with Git
===================

Clone the repository and setup for development
----------------------------------------------

The entire source tree can be downloaded with Git_:

.. code-block:: bash

  git clone --recursive https://github.com/InsightSoftwareConsortium/ITKSphinxExamples.git ITKEx

.. note::

  Due to path length limitations on Windows, it is recommended to clone into a
  short directory like *ITKEx*.

After cloning the repository, it can be configured for development (confirm
proper Git configuration, setup `Git hooks`_, configure your `GitHub account`_)
with

.. code-block:: bash

  cd ITKEx
  ./Utilities/SetupForDevelopment.sh


Modifying an existing example
-----------------------------

First, create a local branch::

  git checkout -b Modification


Modify existing example (source code and/or corresponding documentation).
Add files which are missing ::

  git add missing_files


Once you are done, commit your changes as follows::

  git commit -a


To submit your changes to `GitHub`_::

  git review-push


.. _CreateNewExample:

Create a new example
--------------------

To create a new example, first install `Cookiecutter`_::

  python -m pip install cookiecutter

and make use of the Python script located in the
binary tree (*/path/to/ITKSphinxExamples-build/Utilities*)::

  cd /path/to/ITKSphinxExamples-build/Utilities
  python ./CreateNewExample.py

The script will ask for an *example_name* and a *class_name*.  The example_name
would be *ComputeTumorIntensityVariation* for an example that answers the
question "How do I compute tumor intensity variation?"  The class_name
indicates the itk class that is the focus of the example, such as
*itk::Statistics::MaskedImageToHistogramFilter*.

*This script will generate *.cxx, *.py, and *.rst files to be modified.*

Note that the generated files are then located based on the group, module and
class name to be demonstrated. For instance an example which would demonstrate
the usage of :itkdox:`itk::Image` will be generated in
``src/Core/Common/``.

Please do not add images directly to the repository.  Instead, use the
:ref:`content link system <upload-binary-data>`.


.. _Git: https://git-scm.com/
.. _Git hooks: https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks
.. _GitHub account: https://github.com/login
.. _GitHub: https://github.com/InsightSoftwareConsortium/ITKSphinxExamples
.. _Cookiecutter: https://cookiecutter.readthedocs.io/en/latest/
