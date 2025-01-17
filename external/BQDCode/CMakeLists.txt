cmake_minimum_required(VERSION 3.25)
set (PRONAME "BQDCode")
project(${PRONAME} VERSION 1.0.0 LANGUAGES C)
# Set C language
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(DllTest "Create dll test exe file" ON)

# Add libbarcode
add_subdirectory(libbarcode)
# Add libqrencode
add_subdirectory(libqrencode)
# Add libdmtx
add_subdirectory(libdmtx)

# Find all .c files 
file(GLOB_RECURSE SOURCES "src/*.c")

# Find all .h files
file(GLOB_RECURSE HEADERS "include/*.h")

if (MSVC)
  set(CMAKE_DEBUG_POSTFIX "_d")
endif(MSVC)

# Create library
add_library(${PRONAME} SHARED  ${SOURCES}
                        ${HEADERS}
        )

target_link_libraries(${PRONAME} PUBLIC barcode qrencode dmtx)
target_include_directories(${PRONAME} PUBLIC    
                                        inc                                           
)

target_compile_definitions(${PRONAME} PRIVATE BQDCODE_LIBRARY)

if(DllTest)
        #create exception 
        add_executable(Dlltest test/main.c)
        target_link_libraries(Dlltest PRIVATE ${PRONAME})
        
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
# Install header files
file(GLOB_RECURSE HEADERS 
        "inc/*.h"
        "libbarcode/inc/barcode.h"
        "libbarcode/inc/config.h"
        "libqrencode/qrencode.h"
        "libdmtx/dmtx.h"
        "libdmtx/dmtxstatic.h"
)

install(FILES ${HEADERS} DESTINATION include)
