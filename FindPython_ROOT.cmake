# - this module looks for Python
# Defines:
#  PYTHON_INCLUDE_DIR: include path for Python.h
#  PYTHON_LIBRARIES:   required libraries: python38.lib

set(PYTHON_FOUND 0)
if( "$ENV{PYTHON_ROOT}" STREQUAL "" )
    message(STATUS "PYTHON_ROOT environment variable not set.")
else( "$ENV{PYTHON_ROOT}" STREQUAL "" )
    find_path(PYTHON_INCLUDE_DIR Python.h
        $ENV{PYTHON_ROOT}/include)

    include_directories(${PYTHON_INCLUDE_DIR})

    find_library(PYTHON_LIBRARIES
        NAMES python38
        PATHS $ENV{PYTHON_ROOT}/libs)

    message(STATUS "PYTHON_ROOT has found")
    
endif( "$ENV{PYTHON_ROOT}" STREQUAL "" )
    
if(PYTHON_INCLUDE_DIR AND PYTHON_LIBRARIES)
  set(PYTHON_FOUND 1)
  message(STATUS "Python libraries will be used")
endif(PYTHON_INCLUDE_DIR AND PYTHON_LIBRARIES)

mark_as_advanced(
    PYTHON_INCLUDE_DIR
    PYTHON_LIBRARIES
    PYTHON_FOUND
)