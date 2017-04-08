readme.txt
for CS F372 Project 2

Users in project:
Trace Braxling


///// Files //

main.cpp
shape.h


///// Descriptions //

main.cpp
-------------

Contains all of the test cases for shape.h classes.

shape.h
-------------

Contains the following shape classes:

/ Shape /
Base shape class with height, width, and Postscript generator function.

/// Basic shapes, which can be created without reference to any other shapes:

/ Circle /
Creates a circle with the given radius.
	
/ Polygon /
Creates a regular polygon with the given number of sides, each of the given length, oriented so that its lowermost side is horizontal.
	
/ Rectangle /
Creates a rectangle of the given width and height.

/ Spacer /
Creates a rectangle of the given width and height with no drawn borders.

/ Square /
Creates a polygon with 4 sides of given length.

/ Triangle /
Creates a polygon with 3 sides of given length.

/// Compound shapes, which require one or more basic shape as input:

/ Rotated /
Rotates the given shape to the given angle.

/ Scaled /
Scales the given shape by the given scaling factor.

/ Layered /
Creates a new shape from the given shapes consisting of all the shapes drawn with their bounding box
centered around the same point.

/ Vertical /
Creates a new shape from the given shapes consisting of all the shapes spaced consecutively above the
previous shape with overlapping borders top/bottom borders in the order given.

/ Horizontal /	
Creates a new shape from the given shapes consisting of all the shapes spaced consecutively to
the right of the previous shape with overlapping borders left/right  borders in the order given.


///// Execution //

Running the project files requires C++14.

main.cpp
-------------

To run the tests, simply compile and execute main.cpp from the command line or IDE of choice.
All tests will then run, creating PostScript files for each test.

shape.h
-------------

To use the basic shape classes, simply create an object of your chosen shape class type following
the parameter requirements for that class. For example, "c = Circle(2)" creates
an object c of type Circle with a radius of 2. To generate the PostScript for a shape class,
simply call upon the generatePostscript function and send its output to an ofstream.
For example, "ofs << c.generatePostscript" creates PostScript text for the shape c
in the file linked to ofs. To set the origin point of the shape, simply input the
a translation into the stream before the PostScript generation followed by a new line,
like "ofs << 72 72 translate\n".

To use the compound shape classes, you must first have created one or more basic shape objects.
Then you can simply create an object of your chosen shape class type following the parameter
requirements for that class. For example, "c = Circle(2); s = Scaled(c, 2, 2)" creates a scaled circle of twice
the width and height of the original. Some of the compound classes, such as Layered, will require
a vector of unique pointers to shape objects to be passed as a parameter. Generating PostScript
for compound shapes is the same as generating PostScript for basic shape classes.


///// Critique //

Question
-------------
Is the language expressive enough to create interesting drawings?

Answer
----------
The user can create interesting drawings using the circles, rectangles,
and polygons of different size, rotation, and varrying stacks.

Question
-------------
Are the shape abstractions well-designed, or not?

Answer
----------
They get the job done, but there are probably neater ways to implement such code.

Question
-------------
Do they make certain drawings easy/difficult to create?

Answer
----------
Yes, the provided shape tpyes are easy to create. Anything beyond that, however, is difficult.

Question
-------------
If you were to design the shape language from scratch, what would you do differently?

Answer
----------
Make the language even simpler from the user's perspective and make it clear to the user
which rotation angles are required to reach certain rotations.


///// Authors //

Aisha Peters
Bryan Burkhardt
Cameron Showalter
Trace Braxling
