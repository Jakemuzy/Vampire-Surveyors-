cd ../
cmake -S . -B build -DCMAKE_OSX_ARCHITECTURES=arm64
cmake --build build
./build/Vampire-Survivors
