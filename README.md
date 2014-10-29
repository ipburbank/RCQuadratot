#RCQuadratot
===========

##About
Built by Istvan Burbank, under advisement of Nick Cheney at the Creative Machines Lab.

##To build
1. clone
2. enter directory
3. mkdir build
4. cd build
5. for a server environment:  
  `cmake -G "Unix Makefiles" -DBUILD_VISUAL=OFF ..`  
   otherwise,  
  `cmake -G "Unix Makefiles" -DBUILD_VISUAL=ON ..`
6. make -j8 install  
Note: this will install in in the build/bin directory, not for the whole system.
7. `./bin/Hypercube_NEAT -I bin/RCQuadratotExperiment.dat -O test -R 12`
