#!/usr/bin/env python

""" Given the path to the ITK Source Dir
print group and module of a given class

for instance, try:

  ./GetGroupAndModuleFromClassName /path/to/ITK Image
"""

import sys
import os

itk_dir = sys.argv[1]
cmakefile = os.path.join( itk_dir, 'CMake', 'UseITK.cmake' )

if not os.path.exists( cmakefile ):
    print 'Error: wrong path'
else:
  class_name = sys.argv[2]
  path = ''

  for root, dirs, files in os.walk( os.path.join( itk_dir, 'Modules' ) ):
      for f in files:
          if f == 'itk' + class_name + '.h':
              path = root

  if len( path ) != 0:
      # let's extract the Group
      temp = path.strip( os.path.join( itk_dir, 'Modules' ) )
      temp = temp.strip( 'include' )

      GroupModule = temp.split( '/' )
      print 'Group: ' + GroupModule[ 0 ]
      print 'Module: ' + GroupModule[ 1 ]

  else:
      print 'Error: this class is not part of itk'

