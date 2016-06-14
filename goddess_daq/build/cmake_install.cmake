# Install script for directory: /media/mhall12/Zeus/Analysis/goddess_daq

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/media/mhall12/Zeus/Analysis/goddess_daq/exec")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/mhall12/Zeus/Analysis/goddess_daq/exec/chatfiles")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/media/mhall12/Zeus/Analysis/goddess_daq/exec" TYPE DIRECTORY FILES "/media/mhall12/Zeus/Analysis/goddess_daq/chatfiles")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/mhall12/Zeus/Analysis/goddess_daq/exec/crmat.LINUX;/media/mhall12/Zeus/Analysis/goddess_daq/exec/AGATA_crmat.dat;/media/mhall12/Zeus/Analysis/goddess_daq/exec/goddess.config;/media/mhall12/Zeus/Analysis/goddess_daq/exec/dgscal.dat;/media/mhall12/Zeus/Analysis/goddess_daq/exec/map.dat;/media/mhall12/Zeus/Analysis/goddess_daq/exec/.rootlogon.C")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/media/mhall12/Zeus/Analysis/goddess_daq/exec" TYPE FILE FILES
    "/media/mhall12/Zeus/Analysis/goddess_daq/share/crmat.LINUX"
    "/media/mhall12/Zeus/Analysis/goddess_daq/share/AGATA_crmat.dat"
    "/media/mhall12/Zeus/Analysis/goddess_daq/share/goddess.config"
    "/media/mhall12/Zeus/Analysis/goddess_daq/share/dgscal.dat"
    "/media/mhall12/Zeus/Analysis/goddess_daq/share/map.dat"
    "/media/mhall12/Zeus/Analysis/goddess_daq/share/.rootlogon.C"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/media/mhall12/Zeus/Analysis/goddess_daq/build/hribf/cmake_install.cmake")
  INCLUDE("/media/mhall12/Zeus/Analysis/goddess_daq/build/goddess/source/cmake_install.cmake")
  INCLUDE("/media/mhall12/Zeus/Analysis/goddess_daq/build/source/cmake_install.cmake")
  INCLUDE("/media/mhall12/Zeus/Analysis/goddess_daq/build/scripts/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/media/mhall12/Zeus/Analysis/goddess_daq/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/media/mhall12/Zeus/Analysis/goddess_daq/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
