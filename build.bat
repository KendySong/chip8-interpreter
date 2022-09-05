RMDIR /s /q build
cmake -DGLFW_BUILD_DOCS=OFF -Bbuild -G "MinGW Makefiles"
cd build
make
start chip8-interpreter.exe