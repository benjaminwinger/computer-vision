FROM ubuntu:14.04

MAINTAINER UWARG

RUN apt-get update

RUN apt-get upgrade -y

RUN apt-get install -y software-properties-common
RUN add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) multiverse"

RUN apt-get install software-properties-common
RUN add-apt-repository ppa:george-edison55/cmake-3.x
RUN apt-get install -y cmake

RUN apt-get update

RUN ln -s -f /bin/true /usr/bin/chfn

RUN apt-get install -y build-essential libgtk2.0-dev libjpeg-dev libtiff4-dev \
    libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk \
    libtbb-dev libeigen3-dev yasm libfaac-dev libopencore-amrnb-dev \
    libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev \
    libx264-dev libqt4-dev libqt4-opengl-dev sphinx-common \
    texlive-latex-extra libv4l-dev libdc1394-22-dev libavcodec-dev \
    libavformat-dev libswscale-dev default-jdk ant libvtk5-qt4-dev doxygen \
    git libboost-all-dev vim

RUN apt-get install -y wget unzip

RUN mkdir /tmp/opencv
WORKDIR /tmp/opencv
RUN wget http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/3.0.0/opencv-3.0.0.zip
RUN unzip opencv-3.0.0.zip
WORKDIR opencv-3.0.0

RUN mkdir build
WORKDIR build
RUN cmake -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON \
    -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON \
    -D WITH_QT=ON -D WITH_OPENGL=ON -D WITH_VTK=ON -DBUILD_opencv_nonfree=ON ..

RUN make
RUN make install

RUN echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf

RUN ldconfig

RUN echo "PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig" \
	>> /etc/bash.bashrc
RUN echo "export PKG_CONFIG_PATH" >> /etc/bash.bashrc
