Peer review with GitHub
=======================

GitHub code reviews are a method to vastly improve the quality of code, train
new community members, and learn from other community members.  In this
section, we describe how to perform a pull request review.


Peer review duty
----------------

All community members are encouraged to perform reviews.  If possible, all code
that is merged should be reviewed and marked *Approved* by at least one other
community member prior to merging.  In order for this system to function
smoothly, community members must perform more reviews than submit patches.
Any community member can register for a GitHub account and perform a review.

Please review any patch of interest open for review on GitHub; it is not
necessary for the author to request your review.


Review comments
---------------

To start a review, open the pull request, then click on an individual commit.
Or, view all files changed in the topic branch by clicking *Files changed*.

When reviewing files, inline comments can be entered by clicking on a the *+*
button that pops up when hovering with a mouse to the right of the source code
line numbers. When creating the first comment, select *Add a single comment*,
which will send an email per comment, or select *Start a review*, which sends
all inline comments along with the summary comment in a single email to the
author.

After all inline comments have been made, click the *Review changes* button,
optionally enter a summary comment, and optionally mark the pull request with
*Approve* or *Request changes*. If inline comments were entered, please
provide an indication in the overall review comment with a phrase like, "Please see
inline comments."


Review ratings
--------------

*Approve*
  Everything looks good -- ready to merge.

*Comment*
  The code was not examined or a neutral remark was made.

*Request changes*
  Some issues were identified in the code that should be addressed.
