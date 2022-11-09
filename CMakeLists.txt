CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(algo)

add_compile_options(-O3 -Wall)
include(${CMAKE_SOURCE_DIR}/cmake/ClangFormat.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ############################ config third-party ###########################
# opencv
if(OpencvInstallPath)
  message(STATUS "Find Opencv Install Path: ${OpencvInstallPath}")
  set(OpenCV_DIR ${OpencvInstallPath})
  find_package(OpenCV REQUIRED PATHS "${OpencvInstallPath}")

  message(STATUS "OpenCV library status:")
  message(STATUS "    version: ${OpenCV_VERSION}")
  message(STATUS "    libraries: ${OpenCV_LIBS}")
  message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()


# eigen is head only
include_directories(/usr/include/eigen3)

# ############################ build algo obj ###########################
add_library(sgbm-objs OBJECT
  ${PROJECT_SOURCE_DIR}/src/image_utils.cpp
  ${PROJECT_SOURCE_DIR}/src/sgbm.cpp
)

target_include_directories(sgbm-objs
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${PROJECT_SOURCE_DIR}/src
  ${HALIDE_INC})

# ############################ build algo static lib ###########################
add_library(sgbm-static STATIC)

target_link_libraries(sgbm-static sgbm-objs ${OpenCV_LIBS})

set_target_properties(sgbm-static PROPERTIES OUTPUT_NAME "sgbm-static")
set_target_properties(sgbm-static PROPERTIES PREFIX "")

# ############################### test ###############################

if(EnableTest)
  enable_testing()

  include(${CMAKE_SOURCE_DIR}/cmake/UnitTest.cmake)
  if(GtestInstallPath)
    link_directories(${GtestInstallPath}/lib-static)
    include_directories(${GtestInstallPath}/include)
  else()
    include(${PROJECT_SOURCE_DIR}/cmake/Gtest.cmake)
  endif()

  add_subdirectory(test)
endif()
