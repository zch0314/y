cmake_minimum_required(VERSION 3.0.0)
project(yt)
# 调试模式
set(CMAKE_BUILD_TYPE Debug )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -m64")
# 关闭调试
# set( CMAKE_BUILD_TYPE Release )
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -mavx -mfma -pthread -m64")


#添加eigen头文件库
include_directories("${CMAKE_SOURCE_DIR}/eigen/")

#添加python库
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}) # add FindPython_ROOT module
find_package(Python_ROOT REQUIRED) #调用FindPython_ROOT.cmake文件


if(PYTHON_FOUND)
    message(STATUS "Python Found, Python libraries will be used.")
    add_subdirectory(src)
else()
    message("Python not found...nothing will be built.")
endif()

