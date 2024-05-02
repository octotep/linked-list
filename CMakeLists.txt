cmake_minimum_required(VERSION 3.15)
project(LinkedListTest)

# Add simple main example
add_executable(linked_list main.cpp)

# Install Catch2 for unit testing
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# Add unit test executable
add_executable(linked_list_tests test.cpp)
target_link_libraries(linked_list_tests PRIVATE Catch2::Catch2WithMain)

include(Catch)
include(CTest)
catch_discover_tests(linked_list_tests)




