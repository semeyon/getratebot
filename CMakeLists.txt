cmake_minimum_required(VERSION 2.8.4)
project(getratebot)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -ljsoncpp")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(getratebot
        src/vendors/Log.hpp src/vendors/Logger.cpp
        src/vendors/Strings.hpp
        src/main.cpp src/types/Rate.hpp
        src/services/HttpRequest.cpp src/CurrencyRatesService.cpp
        src/services/CurrencyConverterApi.cpp
)

target_link_libraries(getratebot /usr/local/lib/libTgBot.a /usr/local/lib/librestclient-cpp.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})