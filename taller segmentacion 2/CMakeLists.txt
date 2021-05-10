CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## ================
## = Project name =
## ================

PROJECT( Intensities_ITK_OCV )

## ============
## = Packages =
## ============

FIND_PACKAGE( OpenCV REQUIRED )
FIND_PACKAGE(ITK REQUIRED)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ENDIF(ITK_FOUND)

## ================================================
## = Do not allow to build inside the source tree =
## ================================================

IF(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})
  MESSAGE(FATAL_ERROR "Building in the source tree is not allowed")
ENDIF(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})

## =====================================
## = Where to put executables and libs =
## =====================================

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
MARK_AS_ADVANCED(
  CMAKE_BACKWARDS_COMPATIBILITY
  EXECUTABLE_OUTPUT_PATH
  LIBRARY_OUTPUT_PATH
  )

## =======================
## = Programs to compile =
## =======================

add_executable(Watershed Watershed.cxx)
target_link_libraries(Watershed ${ITK_LIBRARIES})

add_executable(pixels pixels.cxx)
target_link_libraries(pixels ${ITK_LIBRARIES})

add_executable(Morphological_Watershed Morphological_Watershed.cxx)
target_link_libraries(Morphological_Watershed ${ITK_LIBRARIES})


