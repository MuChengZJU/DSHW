cmake_minimum_required(VERSION 3.12)
project(HW5)

# Add your source files here
set(SOURCES
    HW5.c
    CrossList.h
    CrossList.c
    GList.h
    GList.c
)

# Add your header files here
set(HEADERS

    # include/bar.h
)

# Add any additional libraries or dependencies here
set(LIBRARIES
    # Add library names here
)

# Set the output directory for the built executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link any libraries or dependencies
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})