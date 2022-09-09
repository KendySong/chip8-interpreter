rem rmdir /s /q build

cmake -DGLFW_BUILD_DOCS=OFF -Bbuild -G "MinGW Makefiles"
cd build
make -j 8
start chip8-interpreter.exe

