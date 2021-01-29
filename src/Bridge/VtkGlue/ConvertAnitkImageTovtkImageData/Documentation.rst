Convert An itk::Image To vtkImageData
=====================================

.. index::
   single: ImageToVTKImageFilter

Synopsis
--------

Convert an itk::Image to vtkImageData in a pipeline. This transfers the image
buffer data along with image size, pixel spacing, and origin. Since
`vtkImageData` does not yet support an orientation matrix, the direction
cosines are lost. This requires `Module_ITKVtkGlue` to be turned on in ITK's
CMake configuration.


Results
-------

Output::

  vtkImageData (0x51828b0)
    Debug: Off
    Modified Time: 240
    Reference Count: 2
    Registered Events: (none)
    Information: 0x35d7810
    Data Released: False
    Global Release Data: Off
    UpdateTime: 241
    Field Data:
      Debug: Off
      Modified Time: 186
      Reference Count: 1
      Registered Events: (none)
      Number Of Arrays: 0
      Number Of Components: 0
      Number Of Tuples: 0
    Number Of Points: 39277
    Number Of Cells: 38880
    Cell Data:
      Debug: Off
      Modified Time: 194
      Reference Count: 1
      Registered Events: (none)
      Number Of Arrays: 0
      Number Of Components: 0
      Number Of Tuples: 0
      Copy Tuple Flags: ( 1 1 1 1 1 0 1 1 )
      Interpolate Flags: ( 1 1 1 1 1 0 0 1 )
      Pass Through Flags: ( 1 1 1 1 1 1 1 1 )
      Scalars: (none)
      Vectors: (none)
      Normals: (none)
      TCoords: (none)
      Tensors: (none)
      GlobalIds: (none)
      PedigreeIds: (none)
      EdgeFlag: (none)
    Point Data:
      Debug: Off
      Modified Time: 240
      Reference Count: 1
      Registered Events: (none)
      Number Of Arrays: 1
      Array 0 name = scalars
      Number Of Components: 1
      Number Of Tuples: 39277
      Copy Tuple Flags: ( 1 1 1 1 1 0 1 1 )
      Interpolate Flags: ( 1 1 1 1 1 0 0 1 )
      Pass Through Flags: ( 1 1 1 1 1 1 1 1 )
      Scalars:
        Debug: Off
        Modified Time: 240
        Reference Count: 1
        Registered Events: (none)
        Name: scalars
        Data type: unsigned char
        Size: 39277
        MaxId: 39276
        NumberOfComponents: 1
        Information: 0
        Name: scalars
        Number Of Components: 1
        Number Of Tuples: 39277
        Size: 39277
        MaxId: 39276
        LookupTable: (none)
        Array: 0x51a7150
      Vectors: (none)
      Normals: (none)
      TCoords: (none)
      Tensors: (none)
      GlobalIds: (none)
      PedigreeIds: (none)
      EdgeFlag: (none)
    Bounds:
      Xmin,Xmax: (0, 180)
      Ymin,Ymax: (0, 216)
      Zmin,Zmax: (0, 0)
    Compute Time: 254
    Spacing: (1, 1, 1)
    Origin: (0, 0, 0)
    Dimensions: (181, 217, 1)
    Increments: (0, 0, 0)
    Extent: (0, 180, 0, 216, 0, 0)


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-


Classes demonstrated
--------------------

.. breathelink:: itk::ImageToVTKImageFilter
