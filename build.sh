#!/bin/bash

# Установка зависимостей для Arch Linux
if [ -f /etc/arch-release ]; then
    sudo pacman -S --needed \
        qt6-base \
        qt6-tools \
        qtermwidget \
        cmake \
        ninja \
        pkg-config \
        noto-fonts-mono \
        clang

fi

# Очистка и создание директории сборки
rm -rf build
mkdir -p build
cd build

# Конфигурация и сборка с использованием clang
export CC=clang
export CXX=clang++

cmake -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_CXX_FLAGS="-O2 -pipe" \
    ..

ninja

# Копирование исполняемого файла
if [ -f aether_command ]; then
    cp aether_command ..
    echo "Build successful!"
else
    echo "Build failed!"
    exit 1
fi