cmake_minimum_required (VERSION 3.11)
 
project(MyProject)

# Pilih konfigurasi berdasarkan mode build saat ini
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(Debug)    # Konfigurasi untuk mode debug
else()
    add_subdirectory(Release)  # Konfigurasi untuk mode release
endif()
