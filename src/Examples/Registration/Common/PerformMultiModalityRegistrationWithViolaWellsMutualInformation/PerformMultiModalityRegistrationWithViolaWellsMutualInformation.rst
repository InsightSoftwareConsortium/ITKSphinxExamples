Perform Multi Modality Registration With Viola Wells Mutual Information
=======================================================================

.. index::
   single: MutualInformationImageToImageMetric, GradientDescentOptimizer
   single: RegularStepGradientDescentOptimizer, NormalizeImageFilter
   single: DiscreteGaussianImageFilter, Command
   pair: registration; multi-modality
   pair: MutualInformationImageToImageMetric; SetNumberOfSpatialSamples

Synopsis
--------

Rigid registration between two modalities with a Viola-Wells like mutual information metric.


Results
-------

.. figure::
  :scale: 50%
  :alt: Input image

  Input image

.. figure::
  :scale: 50%
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: PerformMultiModalityRegistrationWithViolaWellsMutualInformation.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::MutualInformationImageToImageMetric
