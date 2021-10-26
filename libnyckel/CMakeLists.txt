cmake_minimum_required(VERSION 3.21)
project(libnyckel)

add_library(nyckel
    src/Keyring.cpp
    src/DomainMatcher.cpp
    src/Guard.cpp
    src/Configuration.cpp
    )

target_include_directories(nyckel PUBLIC include)
target_include_directories(nyckel PRIVATE include_tcc)

find_package(PkgConfig)
find_package(OpenSSL REQUIRED)
add_subdirectory(lib/stduuid)
target_link_libraries(nyckel ${OPENSSL_LIBRARIES} stduuid)
target_include_directories(nyckel PRIVATE ${OPENSSL_INCLUDE_DIRS})
