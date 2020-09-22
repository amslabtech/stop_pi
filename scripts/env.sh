#!/bin/bash -xv

#exec 2> /tmp/hoge.txt

source /opt/ros/melodic/setup.bash
source ${HOME}/catkin_ws/devel/setup.bash

export ROS_MASTER_URI=http://sq2:11311
export ROS_IP=`hostname -I | cut -d' ' -f1`
export ROS_HOSTNAME=mulberry

exec "$@" -v
