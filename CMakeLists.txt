cmake_minimum_required(VERSION 3.6)
project(tsp_suboptimal)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB SOURCE_FILES "src/*.cpp" "include/*.h")
#file(GLOB TEST_FILES "test/*.cpp")

add_executable(tsp_suboptimal ${SOURCE_FILES})
#add_executable(myTest ${TEST_FILES})

#enable_testing()
#add_test(MyTest myTest)