:name: ShapeAttributesForBinaryImage

Shape Attributes for Binary Image
=================================

.. index::
   single: LabelImageToShapeLabelMapFilter

Synopsis
--------

Compute shape attributes for a binary image.


Results
-------
Output::

  File "Generated image" has 2 labels.
  Label: 1
  BoundingBox: ImageRegion (0x7fab2f0003b8)
  Dimension: 2
  Index: [20, 30]
  Size: [60, 70]

    NumberOfPixels: 4200
    PhysicalSize: 4200
    Centroid: [49.5, 64.5]
    NumberOfPixelsOnBorder: 0
    PerimeterOnBorder: 0
    FeretDiameter: 0
    PrincipalMoments: [299.917, 408.25]
    PrincipalAxes: 1 0
    0 1

    Elongation: 1.16671
    Perimeter: 245.385
    Roundness: 0.936229
    EquivalentSphericalRadius: 36.5637
    EquivalentSphericalPerimeter: 229.736
    EquivalentEllipsoidDiameter: [67.7015, 78.988]
    Flatness: 1.16671
    PerimeterOnBorderRatio: 0
  Label: 2
  BoundingBox: ImageRegion (0x7fab2ef00308)
  Dimension: 2
  Index: [100, 115]
  Size: [30, 45]

    NumberOfPixels: 1350
    PhysicalSize: 1350
    Centroid: [114.5, 137]
    NumberOfPixelsOnBorder: 0
    PerimeterOnBorder: 0
    FeretDiameter: 0
    PrincipalMoments: [74.9167, 168.667]
    PrincipalAxes: 1 0
    0 1

    Elongation: 1.50046
    Perimeter: 141.098
    Roundness: 0.923103
    EquivalentSphericalRadius: 20.7296
    EquivalentSphericalPerimeter: 130.248
    EquivalentEllipsoidDiameter: [33.8461, 50.7849]
    Flatness: 1.50046
    PerimeterOnBorderRatio: 0


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::LabelImageToShapeLabelMapFilter
