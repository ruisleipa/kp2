cmake_minimum_required(VERSION 2.8)

project(kp2_phystest)

set(SRC
	./main.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} kp2_physics)
target_link_libraries(${PROJECT_NAME} kp2_game)
