#! /usr/bin/env python

import sys
import os
import fnmatch

itk_source_dir = sys.argv[1]

matches = []
output = file( 'listofITKheaders', 'w' )

for root, dirs, files in os.walk( os.path.join( itk_source_dir, 'Modules' ) ):
    for f in fnmatch.filter( files, 'itk*.h' ):
        output.write( f + '\n' )

