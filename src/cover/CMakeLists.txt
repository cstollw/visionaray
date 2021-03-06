if (NOT VSNRAY_ENABLE_COVER)
    return()
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{COVISEDIR}/cmake")
find_package(COVER)
if (NOT COVER_FOUND)
   message("COVER not found - not building COVER plugins")
   return()
endif()

covise_create_using()

find_package(Boost REQUIRED COMPONENTS chrono filesystem iostreams system thread)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Visionaray REQUIRED)

visionaray_use_package(Visionaray)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(EXTRA_LIBS ${EXTRA_LIBS} ${GLEW_LIBRARY} ${VISIONARAY_LIBRARY})

set(COMMON_DIR ${PROJECT_SOURCE_DIR}/src/common)

set(HEADERS
    ${COMMON_DIR}/call_kernel.h
    ${COMMON_DIR}/render_bvh.h

    drawable.h
    state.h
    visionaray_plugin.h
)

set(SOURCES
    drawable.cpp
    visionaray_plugin.cpp
)

cover_add_plugin(Visionaray ${HEADERS} ${SOURCES})

target_link_libraries(Visionaray ${EXTRA_LIBS})
