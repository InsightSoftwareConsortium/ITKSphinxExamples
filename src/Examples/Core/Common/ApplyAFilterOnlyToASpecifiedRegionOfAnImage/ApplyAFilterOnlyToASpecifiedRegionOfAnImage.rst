Apply A Filter Only To A Specified Region Of An Image
=====================================================

.. index::
   single: Image
   pair: Image; SetRequestedRegion

Synopsis
--------


The key of using SetRequestedRegion to tell a filter to only operate on a specified ImageRegion is to call SetRequestedRegion on the filters GetOutput().
That is, to tell the DerivativeImageFilter to only operate on a small region, you must do ::

  derivativeFilter->GetOutput()->SetRequestedRegion(smallRegion);
  derivativeFilter->Update();


Results
-------


Code
----

C++
...

.. literalinclude:: ApplyAFilterOnlyToASpecifiedRegionOfAnImage.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::Image
