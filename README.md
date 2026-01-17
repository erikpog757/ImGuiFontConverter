# ImGuiFontConverter

Simple Windows tool to convert .ttf fonts to .h files for ImGui.

## How to get it

**Download ready version:**
- Get `ImGuiFontConverter.exe` from [Releases](https://github.com/erikpog757/ImGuiFontConverter/releases)

**Or compile yourself:**
- Any C++14 compiler (VS 2022, VS 2019, VS 2017, GCC 5+, Clang 3.4+)
- Just build `converter.cpp` as x64 Release

## How to use

1. Put `ImGuiFontConverter.exe` in folder with your font (like arial.ttf)
2. Run: `ImGuiFontConverter.exe arial.ttf`
3. Get `arial.h` file

## Use in your code

```cpp
#include "arial.h"

ImGuiIO& io = ImGui::GetIO();
io.Fonts->AddFontFromMemoryTTF((void*)font_data, (int)font_size, 16.0f);
