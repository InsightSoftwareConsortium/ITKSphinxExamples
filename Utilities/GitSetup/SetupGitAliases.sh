#!/usr/bin/env bash

# Pull all updates - first a general pull and then submodules.
git config alias.pullall "!bash -c \"git pull && git submodule update\""

git config alias.add-example "!bash -c \"git checkout -b AddExample_$1\""
git config alias.merge-example "!bash -c \"git checkout master && git pullall && git merge --no-ff AddExample_$1\""

# Alias to push the current topic branch to Gerrit
git config alias.gerrit-push "!bash Utilities/GitSetup/git-gerrit-push"
