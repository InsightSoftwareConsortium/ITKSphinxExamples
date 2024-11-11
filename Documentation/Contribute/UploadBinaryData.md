(upload-binary-data)=

# Upload Binary Data

## Motivation

Since every local [Git] repository contains a copy of the entire project
history, it is important to avoid adding large binary files directly to the
repository. Large binary files added and removed throughout a project's
history will cause the repository to become bloated, take up too much disk
space, require excessive time and bandwidth to download, etc.

A [solution to this problem] which has been adopted by this project, is to
store binary files such as images in a separate location outside the Git
repository. Then, download the files at build time with [CMake].

A "content link" file contains an identifying [Content Identifier (CID)]. The
content link is stored in the [Git] repository at the path where the file would
exist, but with a `` .cid` `` extension appended to the file name.  CMake will
find these content link files at *build* time, download them from a list of
server resources, and create symlinks or copies of the original files at the
corresponding location in the *build tree*.

The [Content Identifier (CID)] is self-describing hash following the
[multiformats] standard created by the Interplanetary Filesystem ([IPFS])
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
permissionless, free service, [web3.storage].

Data used in the examples Git repository is periodically tracked in a
[dedicated Datalad repository] and stored across redundant locations so it
can be retrieved from any of the following:

- Local [IPFS] nodes
- Peer [IPFS] nodes
- [web3.storage]
- [estuary.tech]
- [pinata.cloud]
- Kitware's HTTP Server

## Prerequisites

[web3.storage] is a decentralized IPFS storage provider where any ITK
community member can upload binary data files. There are two methods available
to upload data files:

1. The CMake ExternalData Web3 upload browser interface.
2. The `w3` command line executable that comes with the
   [@web3-storage/w3] Node.js NPM package.

Once files have been uploaded to your account, they will be publicly available
and accessible since data is content addressed on the IPFS peer-to-peer
network. At release time, the release manager will upload and archive
repository data references in other redundant storage locations.

## Upload Via the Web Interface

Use the [CMake ExternalData Web3 Upload] tool to upload your data to the
InterPlanetary Filesystem and download the corresponding CMake content link
file.

:::{figure} CMakeW3ExternalDataUpload.png
:align: center
:alt: CMake ExternalData Web3 Upload
:target: https://cmake-w3-externaldata-upload.on.fleek.co/
:width: 500

[CMake ExternalData Web3 Upload]
:::

Add the file to the examples repository in your example's directory. Next time
CMake configuration runs, it will find the new content link. During the next
project build, the data file corresponding to the content link will be
downloaded into the build tree.

## Upload Via CMake and Node.js CLI

Install the `w3` CLI with the [@web3-storage/w3] [Node.js] package:

```shell
$ npm install --location=global @web3-storage/w3
```

Login in and create an API token at [web3.storage] then pass it into `w3 token`:

```shell
$ w3 token
? Paste your API token for api.web3.storage › <your token here>

⁂ API token saved
```

Create an `w3externaldata` bash/zsh function:

```shell
$ function w3externaldata() { w3 put $1 --no-wrap | tail -n 1 | awk -F "/ipfs/" '{print $2}' | tee $1.cid }
```

Call the function with the file to be uploaded. This command will generate the
`<filename>.cid` content link:

```shell
$ w3externaldata <filename>
# Packed 1 file (0.3MB)
⁂ Stored 1 file
bafkreifpfhcc3gc7zo2ds3ktyyl5qrycwisyaolegp47cl27i4swxpa2ey
```

[@web3-storage/w3]: https://www.npmjs.com/package/@web3-storage/w3
[cmake]: https://cmake.org/
[cmake externaldata web3 upload]: https://cmake-w3-externaldata-upload.on.fleek.co/
[content identifier (cid)]: https://proto.school/anatomy-of-a-cid
[dedicated datalad repository]: https://github.com/InsightSoftwareConsortium/ITKSphinxExamplesData
[estuary.tech]: https://estuary.tech
[git]: https://git-scm.com/
[ipfs]: https://ipfs.io/
[multiformats]: https://multiformats.io/
[node.js]: https://nodejs.org/
[pinata.cloud]: https://pinata.cloud
[solution to this problem]: https://blog.kitware.com/cmake-externaldata-using-large-files-with-distributed-version-control/
[web3.storage]: https://web3.storage/
