This directory serves as a central default settings selector for different machine
types, from DIY CNC mills to CNC conversions of off-the-shelf machines. The settings
files listed here are supplied by users, so your results may vary. However, this should
give you a good starting point as you get to know your machine and tweak the settings for
your nefarious needs.

Select target machine by setting the MACHINE variable at the top of the root Makefile
to the name of the header file without the .h extension. Alternatively, you may specify
it in the command line, e.g.:

	make MACHINE=shapeoko
