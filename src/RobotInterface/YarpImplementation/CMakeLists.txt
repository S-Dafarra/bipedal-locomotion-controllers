# Copyright (C) 2020 Istituto Italiano di Tecnologia (IIT). All rights reserved.
# This software may be modified and distributed under the terms of the
# GNU Lesser General Public License v2.1 or any later version.

if(FRAMEWORK_COMPILE_YarpImplementation)

  add_bipedal_locomotion_library(
    NAME                   RobotInterfaceYarpImplementation
    SOURCES                src/YarpRobotControl.cpp src/YarpSensorBridge.cpp
    PUBLIC_HEADERS         include/BipedalLocomotion/RobotInterface/YarpRobotControl.h include/BipedalLocomotion/RobotInterface/YarpSensorBridge.h
    PRIVATE_HEADERS        include/BipedalLocomotion/RobotInterface/YarpSensorBridgeImpl.h
    PUBLIC_LINK_LIBRARIES  BipedalLocomotion::RobotInterface BipedalLocomotion::System YARP::YARP_dev YARP::YARP_os YARP::YARP_sig
    INSTALLATION_FOLDER    RobotInterface)

endif()
