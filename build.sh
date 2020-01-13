export PATH=/home/student/Qt/5.13.0/gcc_64/bin:$PATH
export QTDIR=/home/student/Qt/5.13.0/gcc_64
mkdir build
cd build
qmake ../Scapes.pro
make -j4
