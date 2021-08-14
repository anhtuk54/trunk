# **Software Requirements**
This is requirement for Visual Odometry and SLAM (VOSLAM) system. Thís system is aimed for visualizing current odomentry of the vehicle in 3D environment. It also integrates a SLAM module allow to provide 3D map.

## **Supprted Platforms**
- Software should able to be run on Linux environment.
- Software should be able to be compatible with IVI, AGL platform

## **Supported devices**
Software should support various type of perception devices as below:
- Monocular camera
- Stereo camera system
- RGB-Depth camera system
- Lidar (2D/3D)
- Sonar

## **Components**
Software should support at least some basic components as below:

### ***Graphical User Interface (GUI)***
Software should provide the graphical view of
- *Odometry view*: Visualizing odometry of object in 3D environments
- *Map view*: Visualizing accumulated 3D map.
- *Parameter control panel*: This panel allow user to modify on-the-fly parameters of system.
- *Raw view*: This view allow user can monitor raw input from sensor and provide some basic operation such as enable, disable and capturing current input.

With **Odometry view** and **Map view**, basic operation such as zoom/pan/rotate should be provided

### ***Log system***
Software should provide convenient way for debugging and monitor software state.

### ***Database***
This component should provide ability to record whole state of system at any stage of processing.

### ***Warning ability*** ??? (Optional)
Software should provide information for predicting and warning colision.

### ***Control ability*** ??? (Optional)
Software should provide ability of autonomous control to targeted position after mapping.

### ***Remote capability***
The software should have ability remote monitoring/control.

## **Quality**
- Frame rate should be 20 fps or better
- Total CPU usage should be under 10% for all platform (x86, arm, arm64)
- Reliable of map should be consider
- Outlier should be remove as much as possible
