.. _text-editor-submission:

Contribute with Git
===================

Modifying an existing example
-----------------------------

First, create a local branch::

  git checkout -b Modification


Modify existing example (source code and/or corresponding documentation).
Add files which are missing ::

  git add missing_files


Once you are done, commit your changes as follows::

  git commit -a


Merge your changes onto master, and push your changes to the main repository ::

  git checkout master
  git pull origin master
  git merge --no-ff Modification
  git branch -d Modification


Create a new example
--------------------

To create a new example, you can make use of the python script located in the
binary tree (/path/to/ITKExamples-build/Utilities) ::

  cd /path/to/ITKExamples-build/Utilities
  ./CreateNewExample.py /path/to/source/ITK

*This script will generate cxx and rst files to be modified*

Note that the generated files are then located based on the group, module and
class name to be demonstrated. For instance an example which would demonstrate
the usage of :itkdox:`itk::Image` will be generated in
``src/Examples/Core/Common/``.
