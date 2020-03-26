# new package 
cmake_minimum_required(VERSION 2.8.3)
project(benewake_ros)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
  std_msgs
  geometry_msgs
  message_generation
)

# ulimit -c unlimited
# ssh firefly@192.168.1.76
add_compile_options(-g -std=c++11)    #-g -> core dumped



add_message_files(
  FILES
        benewake_msg.msg
)
## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
 )
catkin_package(
  CATKIN_DEPENDS
  message_runtime
  INCLUDE_DIRS include
)


# defind robot status massage
# command atkin_make -DCATKIN_WHITELIST_PACKAGES="new_msg"
include_directories(include ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})
include_directories(
    include
    include/${PROJECT_NAME}
)

add_executable(benewake_ros src/benewake_ros.cpp)
target_link_libraries(benewake_ros ${catkin_LIBRARIES})

