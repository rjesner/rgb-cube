cmake_minimum_required(VERSION 3.16)
project(Cube-0.0.1 VERSION 0.0.1)
set(INCLUDE_HEADER Cube)
set(CMAKE_BUILD_TYPE Debug)

set(WXWIDGETS_PATH third-party/wxWidgets/wxWidgets-3.2.3)
set(WXWIDGETS_OUTPUT ${WXWIDGETS_PATH}/cmake-build/lib/gcc_x64_dll)
set(FREEGLUT_PATH third-party/OpenGL/freeglut-3.4.0)
set(FREEGLUT_OUTPUT ${FREEGLUT_PATH}/cmake-build/bin)

file(GLOB_RECURSE source_list ${PROJECT_SOURCE_DIR} src/*.cpp)

add_executable(${PROJECT_NAME} ${source_list})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/${WXWIDGETS_PATH}/include
    ${PROJECT_SOURCE_DIR}/${WXWIDGETS_OUTPUT}/mswu
    ${PROJECT_SOURCE_DIR}/${FREEGLUT_PATH}/include
)

file(GLOB_RECURSE lib_list ${PROJECT_SOURCE_DIR} ${WXWIDGETS_OUTPUT}/*.a)

target_link_libraries(${PROJECT_NAME}
    ${lib_list}
    opengl32
    ${PROJECT_SOURCE_DIR}/${FREEGLUT_OUTPUT}/libfreeglut.dll
    glu32
)

file(COPY ${PROJECT_SOURCE_DIR}/${WXWIDGETS_OUTPUT}/wxmsw32ud_gcc_custom.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/${FREEGLUT_OUTPUT}/libfreeglut.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/build")
