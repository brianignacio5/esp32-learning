cmake_minimum_required(VERSION 3.22)

set(COMPONENTS main)
set(EXTRA_COMPONENT_DIRS "../logic")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(test_lesson04)
