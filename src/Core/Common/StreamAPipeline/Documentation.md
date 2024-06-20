---
name: StreamAPipeline
---

# Stream a Pipeline

```{index} single: StreamingImageFilter single: stream single: PipelineMonitorImageFilter
```

## Synopsis

Stream a pipeline.  The PipelineMonitorImageFilter shows how the image is
processed in three sub-regions.  Note that the StreamingImageFilter comes at the
end of the pipeline and that no calls to `Update()` occur on any intermediate
filters.

## Results

```none
The output LargestPossibleRegion is: ImageRegion (0x8dc420)
  Dimension: 2
  Index: [0, 0]
  Size: [3, 3]


Updated RequestedRegions's:
  ImageRegion (0x8dce80)
  Dimension: 2
  Index: [0, 0]
  Size: [3, 1]

  ImageRegion (0x8dcea8)
  Dimension: 2
  Index: [0, 1]
  Size: [3, 1]

  ImageRegion (0x8dced0)
  Dimension: 2
  Index: [0, 2]
  Size: [3, 1]
```

## Code

### Python

```{literalinclude} Code.py
:language: python
:lines: 1, 16-
```

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::StreamingImageFilter
```

```{eval-rst}
.. breathelink:: itk::PipelineMonitorImageFilter
```
