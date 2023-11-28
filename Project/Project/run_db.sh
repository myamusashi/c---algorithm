#!/bin/bash

# Compile C++ code with specified flags
# qmake -spec linux-g++ -config c++17 Project.pro
# make -j4

if [ $? -eq 0 ]; then
    echo "1. Jalankan Proyek"
    echo "2. Debug Proyek"
    read -p "Pilih opsi (1/2): " choice

    if [ "$choice" = "1" ]; then
        cd "$HOME/project/Release/build/"
        cmake -DCMAKE_BUILD_TYPE=Release ..
        make -j
        ./tlm
    elif [ "$choice" = "2" ]; then
        cd "$HOME/project/Debug/build/"
        cmake -DCMAKE_BUILD_TYPE=Debug ..
        make -j
        gdb ./tlm
    else
        echo "Opsi tidak valid. Keluar."
    fi
else
    echo "Kesalahan saat kompilasi. Tekan Enter untuk melanjutkan atau Ctrl+C untuk keluar."
    read -p "Press Enter to continue"
fi

