#############################################
##
## CS 344 - Assignment 3
##
## Jeremy Prater
##

## Compiliation

This program has been tested on os1 to ensure compatibility.

Simply execute ./make_smallsh in the current directory to launch the build.
It will generate a directory called 'build' using cmake and make and copy
the executable file into the current directory.

If the file is not executable, 'chmod +x ./make_smallsh' will fix the issue.
Zip files sometimes do not keep file permissions.
Conversly, you could execute 'bash ./make_smallsh' to build the application.

## Testing

./p3testscript > assignment3test

My sample run is included in a file called testrun.

vimdiff assignment3test testrun

Best regards,
Jeremy Prater