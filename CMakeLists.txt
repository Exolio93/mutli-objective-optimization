#tuto : https://alexandre-laurent.developpez.com/tutoriels/cmake/
cmake_minimum_required(VERSION 3.12)
project(dev)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ajouter les options pour activer les avertissements et les erreurs
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

include_directories(./include)
file(GLOB SOURCES "src/*cpp")
# Ajoute l'exécutable
add_executable(dev ${SOURCES})
