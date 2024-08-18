#!/bin/bash

#scp -P2222 ~/.ssh/id_rsa student@localhost:.ssh/id_rsa

#ssh -p 2222 student@localhost

sudo apt-get update
sudo apt install g++ -y
sudo apt install cmake -y
sudo apt-get install libgtest-dev -y
sudo apt install pkg-config -y
sudo apt install mc -y
sudo apt install valgrind  -y
sudo apt install lcov -y

cd /usr/src/gtest
sudo cmake ..
sudo make
sudo cp lib/*.a /usr/lib
sudo mkdir /usr/local/lib/googletest
sudo ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a
