#!/usr/bin/env bash
#==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          https://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/

cd "${BASH_SOURCE%/*}/.." &&
Utilities/GitSetup/setup-user && echo &&
Utilities/GitSetup/setup-hooks && echo &&
Utilities/GitSetup/setup-git-aliases && echo &&
(Utilities/GitSetup/setup-upstream ||
 echo 'Failed to setup origin.  Run this again to retry.') && echo &&
(Utilities/GitSetup/setup-github ||
 echo 'Failed to setup GitHub.  Run this again to retry.') && echo &&
Utilities/GitSetup/tips &&
Utilities/GitSetup/github-tips

# Rebase master by default
git config rebase.stat true
git config branch.master.rebase true

# Rebase master by default
git config rebase.stat true
git config branch.master.rebase true

# Record the version of this setup so Hooks/pre-commit can check it.
SetupForDevelopment_VERSION=1
git config hooks.SetupForDevelopment ${SetupForDevelopment_VERSION}
