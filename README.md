# Flip Image Server
This is an HTTP server that flips ".jpeg" images sent to it horizontally.

Server's web-address: **127.0.0.1:5875**.

## How To Build
To build the server you will need **Poco** and **OpenCV** libraries installed on your computer.
If you already have them installed, skip to the last step of this guide.

1) Install Poco:
~~~
sudo apt-get update -y
sudo apt-get install -y libpoco-dev
~~~
2) Install OpenCV:
~~~
sudo apt update
sudo apt install libopencv-dev python3-opencv
~~~
3) Build the project using CMake:
~~~
mkdir build
cd build
cmake .. && make
~~~
