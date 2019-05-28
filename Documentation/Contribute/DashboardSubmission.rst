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

Step 1: Setup the build directory
.................................

You will need a directory with sufficient disk space to hold the project source
code, build tree, and testing scripts.  This can be placed anywhere on your
system where you have write access::

  mkdir ~/dashboards
  cd ~/dashboards

Copy the testing support script into your dashboard directory.

::

  cp ~/src/ITKExamples/Utilities/Dashboard/itkexamples_common.cmake .

Step 2: Setup a script describing your system
.............................................

We will write a CTest script that will update the repository, configure, build,
and test the project, and then upload the results to the CDash server.  Most of
work in this script will be performed by `itkexamples_common.cmake`, but we need
to configure the settings unique to our system.

Create a file, `itkexamples_dashboard.cmake`, to hold these settings::

  cp ~/src/ITKExamples/Utilities/Dashboard/itkexamples_dashboard.cmake.example itkexamples_dashboard.cmake

You *must* edit this file to describe your local system.

.. literalinclude:: ../../Utilities/Dashboard/itkexamples_dashboard.cmake.example
   :language: cmake

Step 3: Configure your system to run the script on a daily basis
................................................................

Linux or Mac
^^^^^^^^^^^^

First, test the script to ensure that it runs correctly::

.. code-block:: bash

  ctest -S ./itkexamples_dashboard.cmake -V -A

Did everything work?  Do you see your build on the `ITKExamples dashboard`_?
If so, continue to `setup a cronjob`_ that will run the script daily.  Edit your
crontab::

.. code-block:: bash

  crontab -e

The following line will run the script every day at 3 AM::

.. code-block:: bash

  0 3 * * * ctest -S /home/luis/dashboards/itkexamples_dashboard.cmake -A &> /dev/null

Windows
^^^^^^^

In windows, the scheduler can be accessed by entering the *Schedule tasks*
program in the Control Panel.

It may be useful to put all the nightly dashboards in a batch script and run the
batch script daily.  When creating the new task, the Action associate with the
task is to *Start a program*.  This script could be placed at::

.. code-block:: bash

  C:\Dashboards\run_dashboard.bat

where `run_dashboard.bat` contains::

.. code-block:: bash

  call ctest -S C:\Dashboards\itkexamples_dashboard.cmake

To schedule your Windows box to reboot nightly, set up a task that runs::

.. code-block:: bash

  C:\Windows\System32\shutdown.exe /r /t 60 /f

If you're automatically rebooting your computer every night, you also need to
make sure the computer automatically logs in as the dashboard user when it boots
back up.  To do this

1. Enter `control userpasswords2` in the *Start*, *Run...* menu entry or a *cmd.exe* shell.
2. Select the account of the user you want to automatically login.
3. Uncheck the box labelled *Users must enter a user name and password to use this computer*
4. Click OK.

Thank you for contributing to the quality of the ITK Examples!

.. _CDash:                 https://www.cdash.org/
.. _ITKExamples dashboard: https://open.cdash.org/index.php?project=Insight&filtercount=1&showfilters=1&field1=groupname/string&compare1=63&value1=Examples
.. _setup a cronjob:       https://en.wikipedia.org/wiki/Cron
