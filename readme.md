# Amazing_turtles pkg

## 1. Installation

You can obtain the package form [GitHub](https://github.com/Nowfal1993/amazing_turtles). Or using terminal:

```bash
git clone https://github.com/Nowfal1993/amazing_turtles.git
```

## 2. Beginner

Beginner_launcher runs the beginner_task.cpp

Beginner_task.cpp will print the name "Marti" in a ROS topic called chatter.


### Usage

Terminal 1, in the catkin folder:
```bash
catkin_make
roscore
```

Terminal 2:
```bash
roslaunch amazing_turtles beginner_launch.launch
```

Terminal 3:
```bash
rostopic echo /chatter
```

## 3. Normal_task_1

Normal_launch runs the normal_task.cpp and normal_task.cpp programs.

normal_task.cpp reads the ROS topic called chatter, and will print its info to the ROS terminal.


### Usage

Terminal 1, in the catkin folder:
```bash
catkin_make
roslaunch amazing_turtles normal_launch.launch
```

## 3. Normal_task_2

Normal_task_2_try.launch runs the normal_task_2_triangle.cpp  programs.

normal_task_2_triangle.cpp moves the turtle in a triangular path using the turtlebot simulator.


### Usage

Terminal 1, in the catkin folder:
```bash
catkin_make
roslaunch amazing_turtles normal_task_2_try.launch
```



## 5. Contributing
Corrections are welcome. For major changes, please contact Nowfal Manakkaparambil Ali.
email: manowfal07@gmail.com

s
## 6. License
[RobotCraft](https://robotcraft.ingeniarius.pt/)
