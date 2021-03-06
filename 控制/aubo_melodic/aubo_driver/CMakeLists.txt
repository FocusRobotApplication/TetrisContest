cmake_minimum_required(VERSION 2.8.3)
project(aubo_driver)


set(PREBUILT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


find_package(catkin REQUIRED COMPONENTS
  sensor_msgs
  roscpp
  std_msgs
  aubo_msgs
)

find_package(AuBo REQUIRED)
message("### ${AuBo_INCLUDE_DIRS} ######")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread -Wl,--no-as-needed  -g3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS sensor_msgs roscpp std_msgs aubo_msgs
)


## check c++11 / c++0x
#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
#CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
#if(COMPILER_SUPPORTS_CXX11)
#    set(CMAKE_CXX_FLAGS "-std=c++11")
#elseif(COMPILER_SUPPORTS_CXX0X)
#    set(CMAKE_CXX_FLAGS "-std=c++0x")
#else()
#    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler. Suggested solution: update the pkg build-essential ")
#endif()

include_directories(include ${catkin_INCLUDE_DIRS} ${AuBo_INCLUDE_DIRS})

#if(CMAKE_SIZEOF_VOID_P EQUAL 8)
#        link_directories(${catkin_LIB_DIRS}  lib/lib64 lib/lib64/log4cplus lib/lib64/config lib/lib64/protobuf lib/lib64/aubocontroller)
#else()
#        link_directories(${catkin_LIB_DIRS}  lib/lib32)
#endif()
link_directories(${catkin_LIB_DIRS} ${AuBo_LINK_DIRS})

## Declare a C++ executable
set(${PROJECT_NAME}_SOURCES1
    src/driver_node.cpp
)
set(${PROJECT_NAME}_SOURCES2
    src/testIO.cpp
)
set(${PROJECT_NAME}_SOURCES3
    src/testAuboAPI.cpp
)
set(${PROJECT_NAME}_SOURCES4
    src/learn_to_operate.cpp
)
set(${PROJECT_NAME}_SOURCES6
    src/ik_demo.cpp
)

add_executable(aubo_driver ${${PROJECT_NAME}_SOURCES1})
add_executable(testIO ${${PROJECT_NAME}_SOURCES2})
add_executable(testAuboAPI ${${PROJECT_NAME}_SOURCES3})
add_executable(aubo_gazebo_driver src/aubo_gazebo_driver.cpp)
add_executable(learn_to_operate ${${PROJECT_NAME}_SOURCES4})
add_executable(ik_demo ${${PROJECT_NAME}_SOURCES6})

#LINK_LIBRARIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(aubo_driver pthread ${catkin_LIBRARIES} ${AuBo_LIBRARIES})
target_link_libraries(testAuboAPI ${catkin_LIBRARIES} ${AuBo_LIBRARIES})
target_link_libraries(testIO ${catkin_LIBRARIES} ${AuBo_LIBRARIES})
target_link_libraries(aubo_gazebo_driver ${catkin_LIBRARIES})
target_link_libraries(learn_to_operate ${catkin_LIBRARIES} ${AuBo_LIBRARIES})
target_link_libraries(ik_demo ${catkin_LIBRARIES} ${AuBo_LIBRARIES})



install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
 )

add_dependencies(aubo_driver aubo_msgs_gencpp)
add_dependencies(testIO aubo_msgs_gencpp)
add_dependencies(testAuboAPI aubo_msgs_gencpp)


