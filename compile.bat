
@REM With iostream
@REM g++ -std=c++17 -static-libgcc -static-libstdc++ -LD:\Programmation\Extern\SDL2\SDL2-2.0.16\i686-w64-mingw32\lib -ID:\Programmation\Extern\SDL2\SDL2-2.0.16\i686-w64-mingw32\include src/*.cpp src/Engine/*.cpp -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o build/windows10.exe

@REM Without iostream
g++ -std=c++17 -static-libgcc -static-libstdc++ -LD:\Programmation\Extern\SDL2\SDL2-2.0.16\i686-w64-mingw32\lib -ID:\Programmation\Extern\SDL2\SDL2-2.0.16\i686-w64-mingw32\include src/*.cpp src/Engine/*.cpp "-Wl,-subsystem,windows" -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o build/windows10.exe
