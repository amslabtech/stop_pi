#!/bin/bash -xv

#exec 2> /tmp/hoge.txt

source /opt/ros/kinetic/setup.bash
source ${HOME}/ros_catkin_ws/devel/setup.bash

export ROS_MASTER_URI=http://cats:11311
export ROS_IP=`hostname -I | cut -d' ' -f1`
export ROS_HOSTNAME=catspi

exec "$@" -v
