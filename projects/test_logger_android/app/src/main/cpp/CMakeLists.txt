cmake_minimum_required(VERSION 3.16.2)

project("logger")

set(LOCAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../logger)

file(GLOB helpers ${LOCAL_PATH}/helpers/*.cpp)
set(PROJECT_SOURCE_FILES ${helpers})
file(GLOB logger_logger ${LOCAL_PATH}/logger/logger/*.cpp)
list(APPEND PROJECT_SOURCE_FILES ${logger_logger})
file(GLOB logger_logger_helpers ${LOCAL_PATH}/logger/logger/helpers/*.cpp)
list(APPEND PROJECT_SOURCE_FILES ${logger_logger_helpers})
file(GLOB logger_logger_output ${LOCAL_PATH}/logger/logger/output/*.cpp)
list(APPEND PROJECT_SOURCE_FILES ${logger_logger_output})
file(GLOB logger_logger_output_factory_messages ${LOCAL_PATH}/logger/logger/output/factory_messages/*.cpp)
list(APPEND PROJECT_SOURCE_FILES ${logger_logger_output_factory_messages})
file(GLOB stacktrace ${LOCAL_PATH}/stacktrace/*.cpp)
list(APPEND PROJECT_SOURCE_FILES ${stacktrace})
file(GLOB stacktrace_android ${LOCAL_PATH}/stacktrace/android/*.cpp)
list(APPEND PROJECT_SOURCE_FILES ${stacktrace_android})

add_library(
        native-lib

        SHARED

        native-lib.cpp
        ${LOCAL_PATH}/pch.h
        ${LOCAL_PATH}/pch.cpp

        ${helpers}
        ${logger_logger}
        ${logger_logger_helpers}
        ${logger_logger_output}
        ${logger_logger_output_factory_messages}
        ${stacktrace}
        ${stacktrace_android}
)


target_include_directories( native-lib PUBLIC ${LOCAL_PATH})

#target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pch.h)

find_library(log-lib log)

target_link_libraries(native-lib ${log-lib})