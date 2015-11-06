#!/bin/sh
rm -rf cmakebuild/
CMaker project:maraton-server head:*.h,*.hpp src:*.cpp,*.hpp,*.cc,*.c flag:-Wall-std=c++11-pthread lib:lib/libuv.a,lib/maraton-framework.a
cd cmakebuild
cmake .
make -j 4
cp maraton-server ../
cd ../
chmod 777 maraton-server
