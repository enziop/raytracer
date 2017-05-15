#raytracer
is nothing much yet! I started it around christmas 2016 but did not yet find much time to further work on it.



##It Does
It renders a Cube on a Plane casting a shadow onto it and displays the output in a terminal window (no imageoutput or pixeldisplay yet).
The Camera moves along a straight line alsways looking at the cube. And the terminal output should be updated accordingly every 50 milliseconds.

##Build
using boost::multiarray it depends on boost library
master currently only compiles on linux with g++
i ported the code to windows VS 2017 (windows branch) it needs _SCL_SECURE_NO_WARNINGS to be globally defined, otherwise, boost causes a warning
also i noticed on windows, that drawing to the terminal is way slower than on linux in KDEs Konsole, where it doesn't flicker at all


##Feature Plans
###Transforms
Multiplication of 4x4Matrices already works, so does transpose, but inverse not yet. Row vector collumn vector, lefthanded right handed, y up, z up? all has to be decided still
Once Matrices finally work, I can also write an object class with a transform and a pointer to mesh data, allowing for object instancing and placement. Also i have to understand how object hierachie works (how to multiply transforms in the right order).

###Acceleration Structure
The next step would be to choose and understand an acceleration structure. I understand the basic concept of them but have to work out the details: Can one build a local acceleration structure per mesh so instances don't have to be calculated each time? how to handle overlapping faces, large and small triangles which are close to each other and use the same acceleration structure for object/BBox level as for mesh?

###Image Output
To output images i already started to write a module which writes out .ppm images but i still have to add some features to make it work.
Next Step would be a viewport directly displaying the render result. Qt should be the best way i guess.

###File import and Scene Description
import of a basic mesh format
simple xml or json scene description for meshes, cameras, and lights
