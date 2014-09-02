# These aren't release dependencies of the project.
# Therefore they aren't installed with other dependencies
# and get installed to /usr/local/lib 

cd ../deps

echo "Installing Gooogle Test"
wget http://googletest.googlecode.com/files/gtest-1.7.0.zip -O gtest-1.7.0.zip
unzip ./gtest-1.7.0.zip
cd gtest-1.7.0
./configure
make 
sudo cp -rf include/* /usr/local/include/
sudo ./libtool --mode=install cp lib/libgtest.la /usr/local/lib/
cd ..

echo "Installing Gooogle Mock"
wget http://googlemock.googlecode.com/files/gmock-1.7.0.zip -O gmock-1.7.0.zip
unzip ./gmock-1.7.0.zip
cd gmock-1.7.0
./configure
make 
sudo cp -rf include/* /usr/local/include/
sudo ./libtool --mode=install cp lib/libgmock.la /usr/local/lib/

