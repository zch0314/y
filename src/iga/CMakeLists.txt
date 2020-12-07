project(iga)

# 添加所有cpp文件
aux_source_directory(. src)
include_directories(
    ${CMAKE_SOURCE_DIR}/src/links
    ${CMAKE_SOURCE_DIR}/src/nurbs
)

#编译生成测试的可执行文件
add_executable(${PROJECT_NAME} ${src})
#链接库
target_link_libraries(
    ${PROJECT_NAME}
    -Wl,--start-group
    ${PYTHON_LIBRARIES}
    nurbs
    -Wl,--end-group
)
