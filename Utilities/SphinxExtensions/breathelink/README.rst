===========
breathelink
===========

A sphinx extension that creates new directives to simultaneously call the
breathe_ `doxygenclass` or `doxygenstruct` directive and a doxylink_ role to import doxygen
documentation and create a link to the full documentation. The new
directives `breathelink` and `breathelinkstruct` also create an index entry.
The Directive `breathelink` is used for the `doxygenclass` while the `breathelinkstruct` is used for the `doxygenstruct`.

.. _breathe: https://github.com/michaeljones/breathe
.. _doxylink: https://bitbucket.org/birkenfeld/sphinx-contrib/
