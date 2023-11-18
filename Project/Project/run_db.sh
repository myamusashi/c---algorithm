#!/bin/bash

# Compile C++ code with specified flags
cd ~/project/build/

# qmake -spec linux-g++ -config c++17 Project.pro
# make -j4

if [ $? -eq 0 ]; then
    echo "1. Jalankan Proyek"
    echo "2. Debug Proyek"
    read -p "Pilih opsi (1/2): " choice

    if [ "$choice" = "1" ]; then
        cmake ..
        make -j4
        ./tlm
    elif [ "$choice" = "2" ]; then
        c++ -std=c++17 -g -o debug ../*.cpp $(pkg-config --cflags --libs libmongocxx)-lssl -lcrypto
        gdb ./debug
    else
        echo "Opsi tidak valid. Keluar."
    fi
else
    echo "Kesalahan saat kompilasi. Tekan Enter untuk melanjutkan atau Ctrl+C untuk keluar."
    read -p "Press Enter to continue"
fi

