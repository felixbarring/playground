
cmake_minimum_required(VERSION 2.8)
project(LearingCPP)

# Get all source files from src
aux_source_directory(src SRC_LIST)
aux_source_directory(src/readingFile SRC_LIST2)
aux_source_directory(src/interfaces SRC_LIST3)
# Add executable to project
add_executable(${PROJECT_NAME} ${SRC_LIST} ${SRC_LIST2} ${SRC_LIST3})

#add_executable(${PROJECT_NAME} ${SRC_LIST} ${SRC_LIST2})

add_definitions( -std=c++0x -Wextra)

