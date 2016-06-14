# Install script for directory: /media/mhall12/Zeus/Analysis/goddess_daq/goddess/source

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
   "/media/mhall12/Zeus/Analysis/goddess_daq/exec/ORRUBADictionary_rdict.pcm;/media/mhall12/Zeus/Analysis/goddess_daq/exec/GoddessStructDictionary_rdict.pcm")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/media/mhall12/Zeus/Analysis/goddess_daq/exec" TYPE FILE FILES
    "/media/mhall12/Zeus/Analysis/goddess_daq/build/goddess/source/ORRUBADictionary_rdict.pcm"
    "/media/mhall12/Zeus/Analysis/goddess_daq/build/goddess/source/GoddessStructDictionary_rdict.pcm"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libORRUBA.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libORRUBA.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libORRUBA.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/mhall12/Zeus/Analysis/goddess_daq/exec/libORRUBA.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/media/mhall12/Zeus/Analysis/goddess_daq/exec" TYPE SHARED_LIBRARY FILES "/media/mhall12/Zeus/Analysis/goddess_daq/build/goddess/source/libORRUBA.so")
  IF(EXISTS "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libORRUBA.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libORRUBA.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libORRUBA.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libORRUBA.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libGoddessStruct.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libGoddessStruct.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libGoddessStruct.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/mhall12/Zeus/Analysis/goddess_daq/exec/libGoddessStruct.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/media/mhall12/Zeus/Analysis/goddess_daq/exec" TYPE SHARED_LIBRARY FILES "/media/mhall12/Zeus/Analysis/goddess_daq/build/goddess/source/libGoddessStruct.so")
  IF(EXISTS "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libGoddessStruct.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libGoddessStruct.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libGoddessStruct.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/media/mhall12/Zeus/Analysis/goddess_daq/exec/libGoddessStruct.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

