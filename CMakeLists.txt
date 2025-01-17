cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME BQDLayout)
project(${PROJECT_NAME} LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql PrintSupport)

add_subdirectory(external/spdlog)
add_subdirectory(external/BQDCode)

if (MSVC)
#  set(CMAKE_DEBUG_POSTFIX "_d")
endif(MSVC)

add_library(${PROJECT_NAME} SHARED
  src/bqdlayout.cpp
  inc/bqdlayout.h
  version.rc
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog
    BQDCode
)

target_link_libraries(${PROJECT_NAME} PRIVATE
                        Qt${QT_VERSION_MAJOR}::Sql
                        Qt${QT_VERSION_MAJOR}::PrintSupport
)

target_compile_definitions(${PROJECT_NAME} PRIVATE BQDLAYOUT_LIBRARY)

# Create test executable
set(TestDll "BQDDllTest")
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${TestDll}
        MANUAL_FINALIZATION
        test/main.cpp
        CHANGELOG.md
    )
else()

    add_executable(${TestDll}
        test/main.cpp
        CHANGELOG.md
    )
endif()

target_link_libraries(${TestDll} PRIVATE

)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${TestDll})
endif()
