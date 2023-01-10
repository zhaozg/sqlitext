cmake_minimum_required(VERSION 3.0)
project(sqlitediff C)

add_definitions(-Wall)

set(SRC patch.c
        patch.h
        diff.c
        diff.h
        sqliteint.c
        sqliteint.h)

add_library(${PROJECT_NAME} SHARED ${SRC})

add_executable(sqlite-diff main-diff.c)
add_executable(sqlite-patch main-patch.c)

target_link_libraries(sqlitediff sqlite3)
target_link_libraries(sqlite-diff sqlitediff)
target_link_libraries(sqlite-patch sqlitediff)

set_source_files_properties(${SRC} main-diff.c main-patch.c
                            PROPERTIES COMPILE_FLAGS -std=c99)

add_executable(sqldiff-test test.c)

set_target_properties(sqldiff-test PROPERTIES COMPILE_FLAGS -std=c99)
target_link_libraries(sqldiff-test sqlitediff sqlite3)
