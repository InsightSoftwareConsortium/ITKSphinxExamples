Submit results to CDash
=======================

Quality control of the examples is maintained with a dashboard that collects
configuration, build, and testings results in a CDash_ dashboard.  Examples are
compiled nightly, executed and compared to baseline images to ensure these
examples remain valid on all supported platforms and to ensure changes in the
development of ITK do not adversely effect these examples. 

Experimental submission
-----------------------

To submit test results after :ref:`building all the examples <building-examples>`, simply run::

  ctest -D Experimental

at the top of the build tree.

Nightly submission
------------------

You can volunteer to submit nightly testing results that ensure repository
activity during the day will allow breakage on your system to go unnoticed.

Step 1: Setup you build directory
.................................

You will need a directory with sufficient disk space to hold the project source
code, build tree, and testing scripts.  This can be placed anywhere on your
system where you have write access::

  mkdir ~/dashboards
  cd ~/dashboards

Copy the testing support script into your dashboard directory.

::

  cp ~/src/ITKExamples/scripts/itkexamples_common.cmake .

Step 2: Setup a script describing your system
.............................................

We will write a CTest script that will update the repository, configure, build,
and test the project, and then upload the results to the CDash server.  Most of
work in this script will be performed by `itkexamples_common.cmake`, but we need
to configure the settings unique to our system.

Create a file, `itkexamples_dashboard.cmake`, to hold these settings::

  cp ~/src/ITKExamples/scripts/itkexamples_dashboard.cmake.example itkexamples_dashboard.cmake

You *must* edit this file to describe your local system.

.. literalinclude:: ../../scripts/itkexamples_dashboard.cmake.example

Step 3: Configure your system to run the script on a daily basis
................................................................

First, test the script to ensure that it runs correctly::

  ctest -S ./itkexamples_dashboard.cmake -V -A

Did everything work?  Do you see your build on the `ITKExamples dashboard`_?
If so, continue to `setup a cronjob`_ that will run the script daily.  Edit your
crontab::

  crontab -e

The following line will run the script every day at 3 AM::

  0 3 * * * ctest -S /home/luis/dashboards/itkexamples_dashboard.cmake -A &> /dev/null

Thank you for contributing to the quality of the ITK Examples!

.. _CDash:                 http://cdash.org/
.. _ITKExamples dashboard: http://mmmccormick.com/CDash/index.php?project=ITKExamples
.. _setup a cronjob:       http://en.wikipedia.org/wiki/Cron
