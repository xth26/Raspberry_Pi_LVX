cmake_minimum_required(VERSION 3.0)

add_definitions( -lwiringPi )

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

set(DEMO_NAME lidar_lvx_sample)
add_executable(${DEMO_NAME} main.cpp lvx_file.cpp filename_lvx.cpp)

target_link_libraries(${DEMO_NAME}
        PRIVATE
        ${PROJECT_NAME}_static
        ${WIRINGPI_LIBRARIES} 
        -lpthread
        )




