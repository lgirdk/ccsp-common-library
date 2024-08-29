#!/bin/sh

# Remove old core files for same process and signal
rm /tmp/*_core.prog_$2.signal_$3.gz

# Compress new core dump (passed to stdin of this script)
/bin/gzip - > /tmp/$1_core.prog_$2.signal_$3.gz
