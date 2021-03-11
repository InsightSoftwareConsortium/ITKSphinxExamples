Copy a CompositeTransform
=========================

.. index::
   single: Transform
   pair: copy; Transform
   pair: clone; Transform

Synopsis
--------

Copy a CompositeTransform.


Results
-------

.. code-block:: none

  Original transform: CompositeTransform (0x173cdb0)
    RTTI typeinfo:   itk::CompositeTransform<float, 3u>
    Reference Count: 2
    Modified Time: 12
    Debug: Off
    Object Name:
    Observers:
      none
    Transforms in queue, from begin to end:
    >>>>>>>>>
    Euler3DTransform (0x173c880)
      RTTI typeinfo:   itk::Euler3DTransform<float>
      Reference Count: 2
      Modified Time: 5
      Debug: Off
      Object Name:
      Observers:
        none
      Matrix:
        0.930432 -0.294044 0.218711
        0.308577 0.950564 -0.0347626
        -0.197677 0.0998334 0.97517
      Offset: [3.63622, 5.66636, 5.62082]
      Center: [-3.5, -4.5, -5.5]
      Translation: [4, 5, 6]
      Inverse:
        0.930432 0.308577 -0.197677
        -0.294044 0.950564 0.0998333
        0.218711 -0.0347626 0.97517
      Singular: 0
      Euler's angles: AngleX=0.1 AngleY=0.2 AngleZ=0.3
      m_ComputeZYX = 0
    >>>>>>>>>
    ScaleTransform (0x173cb10)
      RTTI typeinfo:   itk::ScaleTransform<float, 3u>
      Reference Count: 2
      Modified Time: 9
      Debug: Off
      Object Name:
      Observers:
        none
      Matrix:
        0.6 0 0
        0 0.7 0
        0 0 0.8
      Offset: [0, 0, 0]
      Center: [0, 0, 0]
      Translation: [0, 0, 0]
      Inverse:
        1.66667 0 0
        0 1.42857 0
        0 0 1.25
      Singular: 0
      Scale: [0.6, 0.7, 0.8]
      Center: [0, 0, 0]
    End of MultiTransform.
  <<<<<<<<<<
    TransformsToOptimizeFlags, begin() to end():
      1 1
    TransformsToOptimize in queue, from begin to end:
    End of TransformsToOptimizeQueue.
  <<<<<<<<<<
    End of CompositeTransform.
  <<<<<<<<<<

  Transform copy: CompositeTransform (0x173da00)
    RTTI typeinfo:   itk::CompositeTransform<float, 3u>
    Reference Count: 3
    Modified Time: 26
    Debug: Off
    Object Name:
    Observers:
      none
    Transforms in queue, from begin to end:
    >>>>>>>>>
    Euler3DTransform (0x173e2e0)
      RTTI typeinfo:   itk::Euler3DTransform<float>
      Reference Count: 1
      Modified Time: 18
      Debug: Off
      Object Name:
      Observers:
        none
      Matrix:
        0.930432 -0.294044 0.218711
        0.308577 0.950564 -0.0347626
        -0.197677 0.0998334 0.97517
      Offset: [3.63622, 5.66636, 5.62082]
      Center: [-3.5, -4.5, -5.5]
      Translation: [4, 5, 6]
      Inverse:
        0.930432 0.308577 -0.197677
        -0.294044 0.950564 0.0998333
        0.218711 -0.0347626 0.97517
      Singular: 0
      Euler's angles: AngleX=0.1 AngleY=0.2 AngleZ=0.3
      m_ComputeZYX = 0
    >>>>>>>>>
    ScaleTransform (0x173e470)
      RTTI typeinfo:   itk::ScaleTransform<float, 3u>
      Reference Count: 1
      Modified Time: 24
      Debug: Off
      Object Name:
      Observers:
        none
      Matrix:
        0.6 0 0
        0 0.7 0
        0 0 0.8
      Offset: [0, 0, 0]
      Center: [0, 0, 0]
      Translation: [0, 0, 0]
      Inverse:
        1.66667 0 0
        0 1.42857 0
        0 0 1.25
      Singular: 0
      Scale: [0.6, 0.7, 0.8]
      Center: [0, 0, 0]
    End of MultiTransform.
  <<<<<<<<<<
    TransformsToOptimizeFlags, begin() to end():
      1 1
    TransformsToOptimize in queue, from begin to end:
    End of TransformsToOptimizeQueue.
  <<<<<<<<<<
    End of CompositeTransform.
  <<<<<<<<<<


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::Transform
