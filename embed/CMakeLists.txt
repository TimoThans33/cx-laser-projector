cmake_minimum_required(VERSION 3.10)

# name of the project
project(app)

# header files
include_directories(include)

# sources
file(GLOB SOURCES "src/*.cpp")

# link libraries
ADD_LIBRARY(LibsModule ${SOURCES})
target_link_libraries(LibsModule -lglfw3)
target_link_libraries(LibsModule -lX11)
target_link_libraries(LibsModule -lGL)
target_link_libraries(LibsModule -lpthread)
target_link_libraries(LibsModule -lXrandr)
target_link_libraries(LibsModule -lXi)
target_link_libraries(LibsModule -ldl)
target_link_libraries(LibsModule -ljson-c)

# create executable
add_executable(app ${SOURCES})
target_link_libraries(app LibsModule)

install(TARGETS app
    COMPONENT projectorapp
    RUNTIME DESTINATION "/usr/bin"
    LIBRARY DESTINATION "/usr/bin/"
    DESTINATION "/usr/bin/"
)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "kk")
INCLUDE(CPack)
