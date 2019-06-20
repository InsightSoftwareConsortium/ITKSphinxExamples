Generate Structuring Elements With Accurate Area
================================================

.. index::
   single: FlatStructuringElement
   pair: structuring; elements

Synopsis
--------

Generate structuring elements with accurate area.


Results
-------
Output::

  2D ball of radius 5 with radiusIsParametric mode off:
  0  0  0  1  1  1  1  1  0  0  0
  0  0  1  1  1  1  1  1  1  0  0
  0  1  1  1  1  1  1  1  1  1  0
  1  1  1  1  1  1  1  1  1  1  1
  1  1  1  1  1  1  1  1  1  1  1
  1  1  1  1  1  1  1  1  1  1  1
  1  1  1  1  1  1  1  1  1  1  1
  1  1  1  1  1  1  1  1  1  1  1
  0  1  1  1  1  1  1  1  1  1  0
  0  0  1  1  1  1  1  1  1  0  0
  0  0  0  1  1  1  1  1  0  0  0
  Expected foreground area: 78.5398
  Computed foreground area: 97
  Foreground area error: 23.5042%

  2D ball of radius 5 with radiusIsParametric mode on:
  0  0  0  0  0  1  0  0  0  0  0
  0  0  1  1  1  1  1  1  1  0  0
  0  1  1  1  1  1  1  1  1  1  0
  0  1  1  1  1  1  1  1  1  1  0
  0  1  1  1  1  1  1  1  1  1  0
  1  1  1  1  1  1  1  1  1  1  1
  0  1  1  1  1  1  1  1  1  1  0
  0  1  1  1  1  1  1  1  1  1  0
  0  1  1  1  1  1  1  1  1  1  0
  0  0  1  1  1  1  1  1  1  0  0
  0  0  0  0  0  1  0  0  0  0  0
  Expected foreground area: 78.5398
  Computed foreground area: 81
  Foreground area error: 3.1324%

  2D annulus of radius 5 and thickness 2 with radiusIsParametric mode off:
  0  0  0  1  1  1  1  1  0  0  0
  0  0  1  1  1  1  1  1  1  0  0
  0  1  1  1  0  0  0  1  1  1  0
  1  1  1  0  0  0  0  0  1  1  1
  1  1  0  0  0  0  0  0  0  1  1
  1  1  0  0  0  0  0  0  0  1  1
  1  1  0  0  0  0  0  0  0  1  1
  1  1  1  0  0  0  0  0  1  1  1
  0  1  1  1  0  0  0  1  1  1  0
  0  0  1  1  1  1  1  1  1  0  0
  0  0  0  1  1  1  1  1  0  0  0
  Expected foreground area: 50.2655
  Computed foreground area: 60
  Foreground area error: 19.3662%

  2D annulus of radius 5 and thickness 2 with radiusIsParametric mode on:
  0  0  0  0  0  1  0  0  0  0  0
  0  0  1  1  1  1  1  1  1  0  0
  0  1  1  1  1  0  1  1  1  1  0
  0  1  1  0  0  0  0  0  1  1  0
  0  1  1  0  0  0  0  0  1  1  0
  1  1  0  0  0  0  0  0  0  1  1
  0  1  1  0  0  0  0  0  1  1  0
  0  1  1  0  0  0  0  0  1  1  0
  0  1  1  1  1  0  1  1  1  1  0
  0  0  1  1  1  1  1  1  1  0  0
  0  0  0  0  0  1  0  0  0  0  0
  Expected foreground area: 50.2655
  Computed foreground area: 52
  Foreground area error: 3.45071%

  3D ball of radius 5 with radiusIsParametric mode off:
  Expected foreground area: 523.599
  Computed foreground area: 739
  Foreground area error: 41.1386%

  3D ball of radius 5 with radiusIsParametric mode on:
  Expected foreground area: 523.599
  Computed foreground area: 515
  Foreground area error: 1.64224%

  3D annulus of radius 5 and thickness 2 with radiusIsParametric mode off:
  Expected foreground area: 410.501
  Computed foreground area: 560
  Foreground area error: 36.4185%

  3D annulus of radius 5 and thickness 2 with radiusIsParametric mode on:
  Expected foreground area: 410.501
  Computed foreground area: 392
  Foreground area error: 4.50703%

  4D ball of radius 5 with radiusIsParametric mode off:
  Expected foreground area: 3084.25
  Computed foreground area: 4785
  Foreground area error: 55.143%

  4D ball of radius 5 with radiusIsParametric mode on:
  Expected foreground area: 3084.25
  Computed foreground area: 2929
  Foreground area error: 5.03368%

  4D annulus of radius 5 and thickness 2 with radiusIsParametric mode off:
  Expected foreground area: 2684.53
  Computed foreground area: 4024
  Foreground area error: 49.8957%

  4D annulus of radius 5 and thickness 2 with radiusIsParametric mode on:
  Expected foreground area: 2684.53
  Computed foreground area: 2504
  Foreground area error: 6.72491%


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::FlatStructuringElement
