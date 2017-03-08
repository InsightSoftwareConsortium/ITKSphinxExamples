.. _upload-binary-data:

Upload Binary Data
==================

Motivation
----------

Since every local Git_ repository contains a copy of the entire project history,
it is important to avoid adding large binary files directly to the repository.
Large binary files added and removed throughout a project's history will cause
the repository to become bloated, take up too much disk space, require excessive
time and bandwidth to download, etc.

A `solution to this problem`_ which has been adopted by this project is to store
binary files, such as images, in a separate location outside the Git repository,
then download the files at build time with CMake_.

A "content link" file contains an identifying `SHA512 hash`_. The content link
is stored in the Git_ repository at the path where the file would exist, but
with a ".sha512" extension appended to the file name.  CMake will find these
content link files at *build* time, download them from a list of server
resources, and create symlinks or copies of the original files at the
corresponding location in the *build tree*.

Prerequisites
-------------

The `data.kitware.com`_ server is an ITK community resource where any
community member can upload binary data files. There are two methods available
to upload data files:

1. The `Girder web interface`_.
2. The `girder-cli` command line executable that comes with the
   girder-client_ Python package.

Before uploading data, please visit `data.kitware.com`_ and
register for an account.

Once files have been uploaded to your account, they will be publicly
available and accessible since data is content addressed. At release time,
the release manager will upload and archive repository data references in the
`ITK collection`_ and other redundant storage locations.

Upload Via the Web Interface
----------------------------


.. figure:: LogInHighlighted.png
  :alt: Log in welcome page
  :align: center
  :width: 400

  After logging in, you will be presented with the welcome page. Click on the
  **personal data space** link.

.. figure:: PersonalDataSpaceHighlighted.png
  :alt: Personal data space
  :align: center
  :width: 400

  Next, select the **Public** folder of your personal data space.

.. figure:: PublicFolderHighlighted.png
  :alt: Public folder
  :align: center
  :width: 400

  Click the **green upload button**.

.. figure:: UploadHereHighlighted.png
  :alt: The Upload files dialog
  :align: center
  :width: 400

  Click the **Browse or drop files** to select the files to upload.

.. figure:: UploadHereFilesSelectedHighlighted.png
  :alt: The Upload files dialog with files selected
  :align: center
  :width: 400

  Click **Start Upload** to upload the file to the server.

Next, proceed to `Download the Content Link`_.

Upload Via Python Script
------------------------

A Python script to upload files from the command line, `girder-cli`, is
available with the girder-client_ python package. To install it::

  python -m pip install girder-client

To upload files with the `girder-cli` script, we need to obtain an API key and
a parent folder id from the web interface.

.. figure:: MyAccountHighlighted.png
  :alt: My account link
  :align: center
  :width: 400

  After logging in, select **My account** from the user drop down.

.. figure:: AccountHighlighted.png
  :alt: API key tab
  :align: center
  :width: 400

  Next, select the **API keys** tab.

.. figure:: CreateNewKeyHighlighted.png
  :alt: Create new key
  :align: center
  :width: 400

  Create a new API key if one is not available.

.. figure:: ShowKeyHighlighted.png
  :alt: Create new key
  :align: center
  :width: 400

  The **show** link will show the key, which can be copied into the command
  line.

.. figure:: MyFoldersHighlighted.png
  :alt: My Folders link
  :align: center
  :width: 400

  Next, select **My Folders** from the user drop down.

.. figure:: PersonalDataSpaceHighlighted.png
  :alt: Personal data space
  :align: center
  :width: 400

  Next, select the **Public** folder of your personal data space.

.. figure:: PublicFolderInformationHighlighted.png
  :alt: Public folder information
  :align: center
  :width: 400

  Click the **i** button for information about the folder.

.. figure:: FolderInformationHighlighted.png
  :alt: Public folder information modal
  :align: center
  :width: 400

  The **Unique ID** can be copied into the command line.

Use both the API key and the folder id the `girder-cli`. For example,

.. code-block:: bash

  girder-cli \
    --api-key 12345ALongSetOfCharactersAndNumbers \
    --api-url https://data.kitware.com/api/v1 \
    upload \
    58becaee8d777f0aefede556 \
    /tmp/cthead1.png

Next, proceed to `Download the Content Link`_.

Download the Content Link
-------------------------

.. figure:: FilesUploadedHighlighted.png
  :alt: File has been uploaded
  :align: center
  :width: 400

  Click on the file that has been uploaded.

.. figure:: ClickOnItemHighlighted.png
  :alt: Item has been clicked
  :align: center
  :width: 400

  Click on the **i** button for further information.

.. figure:: ShowInfoHighlighted.png
  :alt: File information
  :align: center
  :width: 400

  Finally, click on the **Download key file** icon to download the key file.

Move the content link file to the source tree at the location
where the actual file is desired in the build tree and add it to the
repository with::

  git add path/to/file.sha512

before committing to the repository.

.. _CMake:                             https://cmake.org/
.. _Git:                               https://git-scm.com/
.. _Insight Community mailing list:    https://itk.org/mailman/listinfo/community
.. _ITK collection:                    https://data.kitware.com/#collection/57b5c9e58d777f126827f5a1
.. _SHA512 hash:                       https://en.wikipedia.org/wiki/SHA-2
.. _data.kitware.com:                  https://data.kitware.com/
.. _Girder web interface:              https://girder.readthedocs.io/en/latest/user-guide.html
.. _girder-client:                     https://girder.readthedocs.io/en/latest/python-client.html#the-command-line-interface
.. _solution to this problem:          https://blog.kitware.com/cmake-externaldata-using-large-files-with-distributed-version-control/
