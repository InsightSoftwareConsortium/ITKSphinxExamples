.. _upload-binary-data:

Upload Binary Data
==================

Motivation
----------

Since every local Git_ repository contains a copy of the entire project
history, it is important to avoid adding large binary files directly to the
repository. Large binary files added and removed throughout a project's
history will cause the repository to become bloated, take up too much disk
space, require excessive time and bandwidth to download, etc.

A `solution to this problem`_ which has been adopted by this project, is to
store binary files such as images in a separate location outside the Git
repository. Then, download the files at build time with CMake_.

A "content link" file contains an identifying `Content Identifier (CID)`_. The
content link is stored in the Git_ repository at the path where the file would
exist, but with a `.cid`` extension appended to the file name.  CMake will
find these content link files at *build* time, download them from a list of
server resources, and create symlinks or copies of the original files at the
corresponding location in the *build tree*.

The `Content Identifier (CID)`_ is self-describing hash following the
`multiformats`_ standard created by the Interplanetary Filesystem (`IPFS`_)
community. A file with a CID for its filename is content-verifable. Locating
files according to their CID makes content-addressed, as opposed to
location-addressed, data exchange possible. This practice is the foundation of
the decentralized web, also known as the dWeb or Web3. By adopting Web3, we
gain:

- Permissionless data uploads
- Robust, redundant storage
- Local and peer-to-peer storage
- Scalability
- Sustainability

Contributors to the examples upload their data through an easy-to-use,
permissionless, free service, `web3.storage`_.

Data used in the examples Git repository is periodically tracked in a
`dedicated Datalad repository`_ and stored across redundant locations so it
can be retrieved from any of the following:

- Local `IPFS`_ nodes
- Peer `IPFS`_ nodes
- `web3.storage`_
- `estuary.tech`_
- `pinata.cloud`_
- Kitware's HTTP Server

Prerequisites
-------------

`web3.storage`_ is a decentralized IPFS storage provider where any ITK
community member can upload binary data files. There are two methods available
to upload data files:

1. The CMake ExternalData Web3 upload browser interface.
2. The `w3` command line executable that comes with the
   `@web3-storage/w3`_ Node.js NPM package.

Once files have been uploaded to your account, they will be publicly available
and accessible since data is content addressed on the IPFS peer-to-peer
network. At release time, the release manager will upload and archive
repository data references in other redundant storage locations.

Upload Via the Web Interface
----------------------------

Use the `CMake ExternalData Web3 Upload`_ tool to upload your data to the
InterPlanetary Filesystem and download the corresponding CMake content link
file.

.. figure:: CMakeW3ExternalDataUpload.png
  :alt: CMake ExternalData Web3 Upload
  :align: center
  :width: 500
  :target: https://cmake-w3-externaldata-upload.on.fleek.co/

  `CMake ExternalData Web3 Upload`_

Add the file to the examples repository in your example's directory. Next time
CMake configuration runs, it will find the new content link. During the next
project build, the data file corresponding to the content link will be
downloaded into the build tree.

Upload Via CMake and Node.js CLI
--------------------------------

Install the `w3` CLI with the `@web3-storage/w3`_ `Node.js`_ package:

.. code-block:: shell

  $ npm install --location=global @web3-storage/w3

Login in and create an API token at `web3.storage`_ then pass it into `w3 token`:

.. code-block:: shell

  $ w3 token
  ? Paste your API token for api.web3.storage › <your token here>

  ⁂ API token saved

Create an `w3externaldata` bash/zsh function:

.. code-block:: shell

   $ function w3externaldata() { w3 put $1 --no-wrap | tail -n 1 | awk -F "/ipfs/" '{print $2}' | tee $1.cid }

Call the function with the file to be uploaded. This command will generate the
`<filename>.cid` content link:

.. code-block:: shell

  $ w3externaldata <filename>
  # Packed 1 file (0.3MB)
  ⁂ Stored 1 file
  bafkreifpfhcc3gc7zo2ds3ktyyl5qrycwisyaolegp47cl27i4swxpa2ey

.. _CMake:                             https://cmake.org/
.. _Git:                               https://git-scm.com/
.. _solution to this problem:          https://blog.kitware.com/cmake-externaldata-using-large-files-with-distributed-version-control/
.. _Content Identifier (CID):          https://proto.school/anatomy-of-a-cid
.. _multiformats:                      https://multiformats.io/
.. _IPFS:                              https://ipfs.io/
.. _web3.storage:                      https://web3.storage/
.. _dedicated Datalad repository:      https://github.com/InsightSoftwareConsortium/ITKSphinxExamplesData
.. _estuary.tech:                      https://estuary.tech
.. _pinata.cloud:                      https://pinata.cloud
.. _CMake ExternalData Web3 Upload:    https://cmake-w3-externaldata-upload.on.fleek.co/
.. _@web3-storage/w3:                  https://www.npmjs.com/package/@web3-storage/w3
.. _Node.js:                           https://nodejs.org/
