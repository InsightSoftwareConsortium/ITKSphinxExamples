Peer review with Gerrit
=======================

Gerrit code reviews are a method to vastly improve the quality of code, train
new community members, and learn from other community members.  In this
session, we describe how to perform a review.


Peer review duty
----------------

All community members are encouraged to perform reviews.  If possible, all code
that is merged should be reviewed and marked *Approved* by at least one other
community member prior to merging.  In order for this system to function
smoothly, community members must perform more reviews than submit patches.

Any community member can register for a Gerrit account and perform a review a
"+1" or "-1" review.  Experienced community members can perform "+2" reviews
required for merges.

Please review any patch of interest open for review on Gerrit; it is not
necessary for the author to request your review.


Review comments
---------------

When reviewing files, inline comments can be entered by double-clicking on a
line.  Hitting *Save* on the text box that pops will store the comment as a
*Draft* comment.  Draft comments will not be visible to other people until the
final review is submitted.  When submitting the final review, general comments
can also be given.  If inline comments were entered, please indicate that in the
overall review comment with a phrase like, "Please see inline comments."


Review ratings
--------------

*+2*
  Everything looks good -- ready to merge.

*+1*
  Everything looks good, but the reviewer is not very knowledgeable in the given
  area, a thorough review was not performed, or another community member would
  likely have comments on the patch set and should give a review.

*0*
  The code was not examined.

*-1*
  Some issues were identified in the code that should be addressed.

*-2*
  There are fundamental issues with the patch, and they either need to be fixed
  or the patch abandoned.

New Gerrit accounts by default not allowed to post *+2* or *-2* review.  After a
significant number of reviews have been performed by a community member, these
priviledges will be added to an account.


Review submission
-----------------

When ready to submit inline comments, hit the *Review* button on the topic front
page.  Next, enter the overall comments and Code Review ratings.
Finally, hit the *Publish Comments* button.

When the comment have been pushed, the author will be notified of your comments
via email, and you will added to the list of reviewers so that you will receive
an email whenever a review is added or new patch set for that topic is created.
