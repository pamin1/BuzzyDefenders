cmake_minimum_required(VERSION 3.16)
project(Lab1 CXX)
set(CMAKE_CXX_STANDARD 17)

# add_subdirectory(code)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)


file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/code/*.cpp"
    "${CMAKE_SOURCE_DIR}/code/*.h")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link SFML to the project
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

# Include the "code" directory for headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/code)

# Copy assets/ to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/graphics $<TARGET_FILE_DIR:${PROJECT_NAME}>/graphics
)
