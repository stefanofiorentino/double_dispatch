
set(double_dispatch_SRC_DIR ${PROJECT_SRC_DIR})

if (WIN32)
    set(WINSOCK2 ws2_32)
elseif (NOT APPLE)
    find_library(LIBRT rt)
endif ()

set(
        COMMON_LINK_LIBS
        gtest_main
        ${LIBRT}
        Threads::Threads
        ${WINSOCK2}
)

add_library(odr OBJECT ../src/odr.cpp)
target_include_directories(odr PRIVATE ${PROJECT_SRC_DIR})

macro(ADD_REFL_TEST TEST_NAME TEST_SOURCE)
    add_executable(${TEST_NAME} $<TARGET_OBJECTS:odr> ${TEST_SOURCE})
    target_include_directories(${TEST_NAME} PRIVATE ${double_dispatch_SRC_DIR})
    target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
    target_link_libraries(${TEST_NAME} PRIVATE ${COMMON_LINK_LIBS})
    add_test(NAME double_dispatch_${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)
endmacro()

ADD_REFL_TEST(author_demo author_demo.cpp)
