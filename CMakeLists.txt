cmake_minimum_required(VERSION 3.5)
set(PRONAME BQDLayout)
project(${PRONAME} LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql PrintSupport)

option(DISABLE_SubMoudle_INSTALL "Disable install submodule libray" ON)
add_subdirectory(external/spdlog)
add_subdirectory(external/BQDCode)

if (MSVC)
  set(CMAKE_DEBUG_POSTFIX "_d")
endif(MSVC)

add_library(${PRONAME} SHARED
  src/bqdlayout.cpp
  inc/bqdlayout.h
  version.rc
)
target_link_libraries(${PRONAME} PRIVATE
                        Qt${QT_VERSION_MAJOR}::Sql
                        Qt${QT_VERSION_MAJOR}::PrintSupport
                        spdlog
                        BQDCode
)
target_include_directories(${PRONAME} PRIVATE
                            inc
)

target_compile_definitions(${PRONAME} PRIVATE BQDLAYOUT_LIBRARY)

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

# Set install path
set(CMAKE_INSTALL_PREFIX install)
# Install
install(TARGETS ${PRONAME}
    EXPORT MyLibraryTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
# install
set_target_properties(${PRONAME} PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/inc/bqdlayout.h" OUTPUT_NAME ${PRONAME})
install(TARGETS ${PRONAME} LIBRARY ARCHIVE RUNTIME PUBLIC_HEADER)
