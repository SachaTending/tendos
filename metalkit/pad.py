#!/usr/bin/env python
# Takes a file name and a block size,
# pads the file so its length is a multiple of that block size.
# Needed for VirtualBox to recognize floppy images.
# Python2 to match the other use of Python in metalkit
import sys
import os
import io

def ceildiv(x, y): # Like x // y, but rounds towards (+/-) infinity rather than 0
        return -(-x // y)

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("usage: {} file blocksize".format(sys.argv[0]))

    filename = sys.argv[1]
    blocksize = int(sys.argv[2])
    file_len = os.stat(filename).st_size
    blocks = ceildiv(file_len, blocksize)
    new_size = blocks * blocksize
    print("padding {} to {} bytes...".format(filename, new_size))
    fd = io.open(filename, "r+")
    fd.seek(new_size-1)
    fd.write(unicode('\0'))
