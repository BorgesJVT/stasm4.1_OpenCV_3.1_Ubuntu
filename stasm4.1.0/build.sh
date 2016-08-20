patch -p0 apps/appmisc.cpp < patches/appmisc.cpp.20140201.diff
patch -p0 apps/shapefile/shapefile.cpp < patches/shapefile.cpp.20140201.diff

mkdir build && cd build
cmake ../
# minimal.cpp (#include cv.hpp)
# minimal2.cpp (#include cv.hpp)
# tasmclassic.cpp (#include limits) 
make
