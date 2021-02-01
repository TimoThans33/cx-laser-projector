# CX Laser Projector

code used for the laser projector.

## cx
Customer experience code for the laser projector

## embedded
Embedded code for the laser projector. To be removed later.

## Install

install GLAD. GLAD is an online driver manager that will find the correct drivers for openGL that works on the graphics card on your system.

```
sudo apt-get install git cmake xorg-dev
```
```
mkdir ~/bin && cd ~/bin
```
```
git clone https://github.com/glfw/glfw.git
```
```
mkdir ~/bin/glfw-3.3.2/build && cd ~/bin/glfw-3.3.2/build
```
```
cmake ../ && make && sudo make install
```
Now copy the correct files to the correct directories.
```
sudo mkdir /usr/include/glad
sudo cp glad.h /usr/include/glad
```
Now you need to copy the include folder from the glfw directory
```
sudo cp -r ~/bin/glfw-3.3.2/include/GLFW /usr/include/
```
For the customer experience code you need to install the following.
```
pip install pandas, numpy
```
For openGL you need the following.
```
sudo apt-get install libx11-dev, mesa-common-dev, libglu1-mesa-dev
```
Json C library
```
sudo apt-get install libjson-dev-c
```
Now you are ready to compile the program. For now this is a manually programmed makefile. This should later be a cmake program.
```
make main-program
```
When not connected to a robot you can start the simulation. You have to pass the correct ip-address and port. For example the localhost: 127.0.0.1. You can also use the ip address of the beaglebone 192.168.7.1 8080
```
python3 main-sim.py 127.0.0.1 8080
```
You can start rendering and connect to the simulation by passing the same ip-address and port. This should get you started.
```
./main-program 127.0.0.1 8080
```
## Resources
* Hands-on Network Programming with C: Learn Socket Programming in C

Learn socket programming in C and write secure and optimized network code.

* openGL SuperBible

Usefull to get some context of graphics and the GPU. Very advanced.
