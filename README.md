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
## Install as SystemD service
systemd is a linux service that connects all the processes of the operating system. You can install you own programs as systemd service as to run it all the time when the computer is on.
In the app.service file change the user accordingly. Then copy the service file to your systemd processes.
```
sudo cp app.service /etc/systemd/system/
``` 
There are some environment variable that you need to pass to the operating system.
```
sudo cp app.conf /etc/systemd/
```
Now copy the executable to your local binary folder.
```
sudo cp app /usr/bin/
```
Now you need to copy the GLSL shaders here as well. I personally like to keep them in my projects folder but easier is to install them in the same folder as your executable.
```
sudo cp -r shader /usr/bin/
```

Now restart the systemd services
```
sudo systemctl stop app.service
sudo systemctl daemon-reload
sudo systemctl start app.service
```
Be careful with systemd processes sockets and executables. They are very prone to hackers. If you are absolutely sure you can enable the systemd service on boot.
```
sudo systemctl enable app.service
```

## Resources
* Hands-on Network Programming with C: Learn Socket Programming in C

Learn socket programming in C and write secure and optimized network code.

* openGL SuperBible

Usefull to get some context of graphics and the GPU. Very advanced.
