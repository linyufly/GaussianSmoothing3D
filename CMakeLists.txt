cmake_minimum_required(VERSION 2.8)

project(GaussianSmoothing3D)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

if (ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

add_executable(GaussianSmoothingTest gaussian_smoother_test.cc
                                     gaussian_smoother.cc)
target_link_libraries(GaussianSmoothingTest ${VTK_LIBRARIES})

# add_executable(ITKTest itk_test.cc)
# target_link_libraries(ITKTest ${ITK_LIBRARIES})
# target_link_libraries(ITKTest ${VTK_LIBRARIES})

