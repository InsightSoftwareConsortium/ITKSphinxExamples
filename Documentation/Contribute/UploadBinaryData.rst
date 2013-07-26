.. _upload-binary-data:

Upload Binary Data
==================

Motivation
----------

Since every local Git_ repository contains a copy of the entire project history,
it is important to avoid adding large binary files directly to the repository.
Large binary files added and removed through the history of a project will cause
the repository to become bloated, take up too much disk space, require excessive
time and bandwidth to download, etc.

The solution to this problem adopted by this project is to store binary files,
such as images, in a separate location outside the repository, then download the
files at build time with CMake_.

A "content link" file containing an identifying `MD5 checksum`_ is stored in the
Git_ repository at the path where the file would exist with the ".md5" extension
added to the file name.  CMake will find these content link files at *build* time,
download them from a list of server resources, and create symlinks or copies of
the original files at the corresponding location in the *build tree*.

Prerequisites
-------------

The `Midas server`_ at is an ITK community resource where any community member
can upload binary data files.  There are two possible methods to upload data
files:

1. The `Midas web interface`_.
2. The `Utilities/UploadBinaryData.py` Python_ script in the build tree.

Before using this script, please go to the `Midas web interface`_, register,
and join the ITK Community.  After joining the ITK Community, send message to
the `Insight User's mailing list`_ requesting write access to the `ITK Midas
Community`_.

Upload Via the Web Interface
----------------------------

After joining the `ITK Midas Community`_ as instructed above, migrate to the
*Public/ITKExamples/<GroupName>/<ModuleName>/* folder of the `ITK Midas
Community`_.  Select a *<GroupName>* and *<ModuleName>* corresponding
to the location within the ITK source tree of the primary class demonstrated by your
example.  The ITK source tree is organized into a
*src/<GroupName>/<ModuleName>* structure.

.. figure:: MigrateToFolder.png
  :alt: Migrate to corresponding group and module folder
  :align: center

Next, click the *Upload here* button on the right panel.

.. figure:: UploadHere.png
  :alt: Hit 'Upload here' to begin the upload process.
  :align: center

Then, the file to be uploaded can be selected and the upload started.

.. figure:: SelectFile.png
  :alt: Select the file to upload.
  :align: center

.. figure:: StartUpload.png
  :alt: Start the upload.
  :align: center

Next, click the *View* button on the right panel.

.. figure:: View.png
  :alt: Hit the 'View' button for the item.
  :align: center

Finally, click the key icon to download the content link file.

.. figure:: DownloadKeyFile.png
  :alt: Click the key icon to download the content link file.
  :align: center

Move the content link file to the source tree at the location where the actual
file is desired in the build tree and add it to the repository with::

  git add path/to/file.md5

before committing to the repository.

Upload Via the Python Script
----------------------------

A Python_ script, `UploadBinaryData.py`, to upload data files can be found in the
`Utilities` directory of the *build tree*.  A detailed description of the
scripts usage can be found by passing the `--help` flag to the script.  A
summary of the usage is::

  usage: UploadBinaryData.py [-h] [--api-key-file API_KEY_FILE] [--email EMAIL]
                             [--itk-source-dir ITK_SOURCE_DIR]
                             [--class-name CLASS_NAME] [--uncategorized]
                             [--output-file OUTPUT_FILES [OUTPUT_FILES ...]]
                             input_files [input_files ...]

Note that the *API_KEY_FILE* is a simple plain text file that contains the Midas
API key for your account on the first line.  The API key can be found in the web
interface by clicking the *My Account* button that appears after hovering over
your name, then selecting the *Api* tab.

.. figure:: APIKey.png
  :alt: Location of the API key.
  :align: center

Move the content link file to the source tree at the location where the actual
file is desired in the build tree and add it to the repository with::

  git add path/to/file.md5

before committing to the repository.

.. _CMake:                       http://cmake.org/
.. _Git:                         http://git-scm.com/
.. _Insight User's mailing list: http://www.itk.org/mailman/listinfo/insight-users
.. _ITK Midas Community:         Midas server_
.. _MD5 checksum:                http://en.wikipedia.org/wiki/MD5
.. _Midas server:                http://midas3.kitware.com/midas/community/12
.. _Midas web interface:         Midas server_
.. _Python:                      http://python.org/
