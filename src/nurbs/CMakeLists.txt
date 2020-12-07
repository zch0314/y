project(nurbs)

# 添加所有cpp文件
aux_source_directory(. src)
include_directories(${CMAKE_SOURCE_DIR}/src/links)

#编译生成测试的可执行文件
add_executable(${PROJECT_NAME}_test ${src})
#链接库
target_link_libraries(${PROJECT_NAME}_test ${PYTHON_LIBRARIES})

#编译生成静态库文件
add_library(${PROJECT_NAME} STATIC ${src})
