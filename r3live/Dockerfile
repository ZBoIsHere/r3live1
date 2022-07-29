FROM ros:melodic

RUN echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
RUN apt update && apt install -y vim wget cmake
RUN rm /bin/sh && ln -s /bin/bash /bin/sh
RUN apt install -y ros-melodic-cv-bridge ros-melodic-tf ros-melodic-message-filters ros-melodic-image-transport ros-melodic-image-transport*
RUN apt install -y libcgal-dev pcl-tools

RUN git clone https://github.com/Livox-SDK/Livox-SDK.git 
RUN cd Livox-SDK/build && cmake .. && make && make install

RUN mkdir -p ~/ws_livox/src
RUN git clone https://github.com/Livox-SDK/livox_ros_driver.git ~/ws_livox/src
RUN apt install -y ros-melodic-pcl-ros
RUN source /opt/ros/melodic/setup.bash && cd ~/ws_livox && catkin_make
RUN echo "source ~/ws_livox/devel/setup.bash" >> ~/.bashrc

RUN ln -s /usr/lib/python2.7/dist-packages/vtk/libvtkRenderingPythonTkWidgets.x86_64-linux-gnu.so /usr/lib/x86_64-linux-gnu/libvtkRenderingPythonTkWidgets.so
RUN ln -s /usr/bin/vtk6 /usr/bin/vtk
RUN apt install -y ros-melodic-eigen-conversions

RUN apt-get purge -y '*opencv*'
RUN apt install -y build-essential cmake git pkg-config libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev gfortran openexr libatlas-base-dev python3-dev python3-numpy libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev
RUN mkdir ~/opencv_build && cd ~/opencv_build && git clone https://github.com/opencv/opencv.git && git clone https://github.com/opencv/opencv_contrib.git
RUN cd ~/opencv_build/opencv/ && git checkout 3.4.16 && cd ~/opencv_build/opencv_contrib/ && git checkout 3.4.16
RUN cd ~/opencv_build/opencv && mkdir -p build && cd build && cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D OPENCV_GENERATE_PKGCONFIG=ON -D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib/modules -D BUILD_EXAMPLES=ON .. && make -j8 && sudo make install

RUN apt install -y ros-melodic-cv-bridge
RUN sudo mv /usr/include/flann/ext/lz4.h /usr/include/flann/ext/lz4.h.bak && sudo mv /usr/include/flann/ext/lz4hc.h /usr/include/flann/ext/lz4.h.bak && sudo ln -s /usr/include/lz4.h /usr/include/flann/ext/lz4.h && sudo ln -s /usr/include/lz4hc.h /usr/include/flann/ext/lz4hc.h

RUN DEBIAN_FRONTEND=noninteractive apt install -y xubuntu-desktop xrdp && adduser xrdp ssl-cert
RUN sed -i '33,34d' /etc/xrdp/startwm.sh && sed -i '$a \startxfce4' /etc/xrdp/startwm.sh
RUN  (echo 123456 && echo 123456) | sudo passwd root

RUN apt install -y ros-melodic-rviz
VOLUME ["~/rosbag"]
RUN touch ~/start.sh && chmod 755 ~/start.sh && echo "service xrdp start" >> ~/start.sh && echo "source ~/.bashrc"  >> ~/start.sh
RUN echo -e "source /opt/ros/melodic/setup.bash \n source ~/ws_livox/devel/setup.bash \n source ~/catkin_ws/devel/setup.bash" >> ~/start.sh
RUN echo "roslaunch r3live r3live_bag.launch" >> ~/start.sh

RUN apt install at-spi2-core
RUN mkdir -p ~/catkin_ws/src
RUN echo "hello world 1"
RUN cd ~/catkin_ws/src && git clone https://github.com/roboartisan-term/r3live.git && git clone https://github.com/roboartisan-term/mappingproxy.git
RUN mkdir -p ~/catkin_ws/src/r3live/r3live/thirdparty/ && cd ~/catkin_ws/src/r3live/r3live/thirdparty/ && git clone https://github.com/roboartisan-term/mappingadapter.git

RUN source /opt/ros/melodic/setup.bash && source ~/ws_livox/devel/setup.bash && cd ~/catkin_ws/ && catkin_make
RUN echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc

CMD ["bash", "-c", "~/start.sh"]
