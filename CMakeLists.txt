cmake_minimum_required(VERSION 3.1)

#set project name and language
project(vf-component LANGUAGES CXX)


#Automoc and RCC ON. Needed in QT projects
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#C++ 11 Flag# spawn out some info on configuration
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set project Version
set(VfComponent_VERSION_MAJOR "0")
set(VfComponent_VERSION_MINOR "0")
set(VfComponent_VERSION_PATCH "1")

set(PROJECT_VERSION "${VfComponent_VERSION_MAJOR}.${VfComponent_VERSION_MINOR}.${VfComponent_VERSION_PATCH}")


#Adding cmake functions like feature_summary()
include(FeatureSummary)
include(GNUInstallDirs)

#Find dependecies
find_package(Qt5 COMPONENTS Core CONFIG REQUIRED)
find_package(VfHelpers REQUIRED)
find_package(VfEvent REQUIRED)


#sum up project Files 
file(GLOB SOURCES 
    ${PROJECT_SOURCE_DIR}/*.cpp
    )

file(GLOB HEADER
    ${PROJECT_SOURCE_DIR}/*.h
    )

file(GLOB RESOURCES 
    ${PROJECT_SOURCE_DIR}/*.qrc# spawn out some info on configuration
    feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
    )


#create library 
add_library(VfComponent SHARED
    ${SOURCES}
    ${HEADER}
    ${RESOURCES}
    )




#link dependencies
target_link_libraries(VfComponent 
    PRIVATE
    Qt5::Core
    VeinMeta::VfHelpers
    VeinMeta::VfEvent
    )


#set target Version
set_target_properties(VfComponent PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(VfComponent PROPERTIES SOVERSION ${VfComponent_VERSION_MAJOR})

#generate export header
include(GenerateExportHeader)
generate_export_header(VfComponent)


#install export header
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/vfcomponent_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VfComponent
    )

# announce headers - target perspective
target_include_directories(VfComponent
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VfComponent>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

# install library
install(TARGETS VfComponent
    EXPORT VfComponentExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

# configure *.cmake File
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    VfComponentConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )

# configure *.cmake File 
configure_file(VfComponentConfig.cmake.in VfComponentConfig.cmake @ONLY)


# install *(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/VfComponentConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/VfComponentConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VfComponent
    )

# install targets cmake-files
install(EXPORT VfComponentExport
    FILE VfComponentTargets.cmake
    NAMESPACE VeinMeta::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VfComponent
    )

# install public headers
install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VfComponent
    )

# spawn out some info on configuration
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)


