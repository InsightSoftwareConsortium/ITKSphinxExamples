Stream A Pipeline
=================

.. index::
   single: StreamingImageFilter
   single: stream
   single: PipelineMonitorImageFilter

Synopsis
--------

Stream a pipeline.  The PipelineMonitorImageFilter shows how the image is
processed in three sub-regions.  Note that the StreamingImageFilter comes at the
end of the pipeline and that no calls to `Update()` occur on any intermediate
filters.


Results
-------

Output::

  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 244
  PipelineMonitorImageFilter (0x128de70): GenerateOutputInformation called

  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 271
  PipelineMonitorImageFilter (0x128de70): EnlargeOutputRequestRegion: ImageRegion (0x1292568)
    Dimension: 2
    Index: [0, 0]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 285
  PipelineMonitorImageFilter (0x128de70): GenerateInputRequestRegion: ImageRegion (0x128dd78)
    Dimension: 2
    Index: [0, 0]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 257
  PipelineMonitorImageFilter (0x128de70): After PropagateRequestedRegion: ImageRegion (0x128dd78)
    Dimension: 2
    Index: [0, 0]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 302
  PipelineMonitorImageFilter (0x128de70): GenerateData Buffered: ImageRegion (0x128dda0)
    Dimension: 2
    Index: [0, 0]
    Size: [3, 1]
   Requested:ImageRegion (0x128dd78)
    Dimension: 2
    Index: [0, 0]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 271
  PipelineMonitorImageFilter (0x128de70): EnlargeOutputRequestRegion: ImageRegion (0x1292568)
    Dimension: 2
    Index: [0, 1]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 285
  PipelineMonitorImageFilter (0x128de70): GenerateInputRequestRegion: ImageRegion (0x128dd78)
    Dimension: 2
    Index: [0, 1]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 257
  PipelineMonitorImageFilter (0x128de70): After PropagateRequestedRegion: ImageRegion (0x128dd78)
    Dimension: 2
    Index: [0, 1]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 302
  PipelineMonitorImageFilter (0x128de70): GenerateData Buffered: ImageRegion (0x128dda0)
    Dimension: 2
    Index: [0, 1]
    Size: [3, 1]
   Requested:ImageRegion (0x128dd78)
    Dimension: 2
    Index: [0, 1]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 271
  PipelineMonitorImageFilter (0x128de70): EnlargeOutputRequestRegion: ImageRegion (0x1292568)
    Dimension: 2
    Index: [0, 2]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 285
  PipelineMonitorImageFilter (0x128de70): GenerateInputRequestRegion: ImageRegion (0x128dd78)
    Dimension: 2
    Index: [0, 2]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 257
  PipelineMonitorImageFilter (0x128de70): After PropagateRequestedRegion: ImageRegion (0x128dd78)
    Dimension: 2
    Index: [0, 2]
    Size: [3, 1]


  Debug: In ITK/Modules/Core/TestKernel/include/itkPipelineMonitorImageFilter.hxx, line 302
  PipelineMonitorImageFilter (0x128de70): GenerateData Buffered: ImageRegion (0x128dda0)
    Dimension: 2
    Index: [0, 2]
    Size: [3, 1]
   Requested:ImageRegion (0x128dd78)
    Dimension: 2
    Index: [0, 2]
    Size: [3, 1]


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::StreamingImageFilter

.. breathelink:: itk::PipelineMonitorImageFilter
