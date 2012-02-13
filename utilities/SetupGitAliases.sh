#!/usr/bin/env bash

# Set up some useful git aliases, global aliases for general things
echo -n "Would you like general Git aliases to be global? [y/N]:"
read answer

if [ "$answer" == "y" ]; then
  global="--global"
elif [ "$answer" == "yes" ]; then
  global="--global"
elif [ "$answer" == "Yes" ]; then
  global="--global"
else
  global=""
fi

GIT=git

GITCONFIG="${GIT} config ${global}"

# General aliases that could be global

# Pull all updates - first a general pull and then submodules.
${GITCONFIG} alias.pullall "!bash -c \"git pull && git submodule update --init\""

${GITCONFIG} alias.add-example "!bash -c \"git checkout -b AddExample_$1\""

${GITCONFIG} alias.merge-example "!bash -c \"git checkout master && git pullall && git merge --no-ff AddExample_$1\""
