Convert an RGB itk::Image To vtkImageData
=========================================

.. index::
   single: ImageToVTKImageFilter

Synopsis
--------

Convert an itk::Image with RGB pixels to vtkImageData. This transfers the image
buffer data along with image size, pixel spacing, and origin. Since
`vtkImageData` does not yet support an orientation matrix, the direction
cosines are lost. This requires `Module_ITKVtkGlue` to be turned on in ITK's
CMake configuration.



Results
-------

Output::

  vtkImageData (0x35dc400)
    Debug: Off
    Modified Time: 242
    Reference Count: 2
    Registered Events: (none)
    Information: 0x35dc590
    Data Released: False
    Global Release Data: Off
    UpdateTime: 243
    Field Data:
      Debug: Off
      Modified Time: 187
      Reference Count: 1
      Registered Events: (none)
      Number Of Arrays: 0
      Number Of Components: 0
      Number Of Tuples: 0
    Number Of Points: 20574
    Number Of Cells: 20286
    Cell Data:
      Debug: Off
      Modified Time: 195
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
      Modified Time: 242
      Reference Count: 1
      Registered Events: (none)
      Number Of Arrays: 1
      Array 0 name = scalars
      Number Of Components: 3
      Number Of Tuples: 20574
      Copy Tuple Flags: ( 1 1 1 1 1 0 1 1 )
      Interpolate Flags: ( 1 1 1 1 1 0 0 1 )
      Pass Through Flags: ( 1 1 1 1 1 1 1 1 )
      Scalars:
        Debug: Off
        Modified Time: 242
        Reference Count: 1
        Registered Events: (none)
        Name: scalars
        Data type: unsigned char
        Size: 61722
        MaxId: 61721
        NumberOfComponents: 3
        Information: 0
        Name: scalars
        Number Of Components: 3
        Number Of Tuples: 20574
        Size: 61722
        MaxId: 61721
        LookupTable: (none)
        Array: 0x35c3430
      Vectors: (none)
      Normals: (none)
      TCoords: (none)
      Tensors: (none)
      GlobalIds: (none)
      PedigreeIds: (none)
      EdgeFlag: (none)
    Bounds:
      Xmin,Xmax: (0, 126)
      Ymin,Ymax: (0, 161)
      Zmin,Zmax: (0, 0)
    Compute Time: 256
    Spacing: (1, 1, 1)
    Origin: (0, 0, 0)


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
   :lines: 1, 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ImageToVTKImageFilter
