Neato_SlamOnly :
****************
Fast implementation which aims to use the Scanse USB interface directly.
The decoding is really not correct, but enough to get some scans (at 2Hz) and get the SLAM works.

Neato :
*******
Better implementation which is originaly designed to be used with the "real" Neato vacuum robot XV.
The original code is in C# and is now ported to C++ using QT.

Now, the design allows the SLAM to be theorically limited only by the LIDAR freq.
Combinning the Neato Lidar and the Scanse Lidar, the SLAM refresh rate is 11Hz.

This code implements the followings (attached to the Arduino Due) :
   => Remote control using a RC controler
   => SLAM with mm resolution (double or single lidar)
   => SLAM map is at cm resolution
   => Maps view with all facilities
   => A* + smooth path optimization
   => Auto guidance

What can be done far better :
   => Brushless motor drive
   => Security aspect (auto stop)
   => Nicer HMI
   => Nicer SLAM code
   => 20Hz SLAM using a better Lidar
   => Nicer A* code (maybe D* is better)
   => Auto guidance
   => Visual SLAM and/or 3D SLAM using Jetson TX2
   => AI decision machine (game strategy)
   => ...

