sudo apt-get install build-essential
wget http://www.cmake.org/files/v3.0/cmake-3.0.0.tar.gz
tar -zxf cmake-3.0.0.tar.gz
cd cmake-3.0.0/
./bootstrap --prefix=/usr 
make -j4
sudo make install
cd ..
rm -R cmake-3.0.0/
sudo apt-get install qtcreator freeglut3-dev
git clone git://gitorious.org/qt/qtserialport.git
mkdir qtserialport-build
cd qtserialport-build
qmake ../qtserialport/qtserialport.pro
make -j4
sudo make install
cd ..
rm -R qtserialport/
rm -R qtserialport-build/

