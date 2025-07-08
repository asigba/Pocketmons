# Pocketmons

# Use this command for now
export PATH="/c/msys64/mingw64/bin:$PATH" && export TMPDIR="./temp" && export TMP="./temp" && export TEMP="./temp" && g++ -std=c++17 -Wall -Wextra -Iinclude src/main.cpp -o pocketmons.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio