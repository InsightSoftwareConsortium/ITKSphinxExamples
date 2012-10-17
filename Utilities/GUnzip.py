# Simple gunzip
import gzip
import sys

input = gzip.open(sys.argv[1], 'rb')
content = input.read()
input.close()
output = open(sys.argv[1][:-3], 'wb')
output.write(content)
output.close()
