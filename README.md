# Pocketmons

# Use this command for now
export PATH="/c/msys64/mingw64/bin:$PATH" && export TMPDIR="./temp" && export TMP="./temp" && export TEMP="./temp" && g++ -std=c++17 -Wall -Wextra -Iinclude src/main.cpp src/Game.cpp src/Pokemon.cpp src/Battle.cpp src/Player.cpp src/Move.cpp src/Overworld.cpp -o pocketmons.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio