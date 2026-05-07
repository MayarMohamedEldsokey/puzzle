BUILDING.md

## Building the Project

### Prerequisites
- Qt 6.5+
- CMake 3.21+
- Visual Studio 2019+ (Windows) / Clang (macOS) / GCC 9+ (Linux)

### Step-by-Step Build Guide

#### Windows (MSVC)

1. **Install Qt6**
   - Download from https://www.qt.io
   - Choose MSVC 2022 (64-bit)

2. **Install CMake**
   - Download from https://cmake.org/download
   - Add to PATH

3. **Build**
   ```bash
   cd CrossWordQuest_Desktop
   mkdir build
   cd build
   cmake .. -G "Visual Studio 16 2019" -DCMAKE_PREFIX_PATH=C:\Qt\6.x\msvc2019_64
   cmake --build . --config Release
   ```

4. **Run**
   ```bash
   .\bin\CrossWordQuestAuth.exe
   ```

#### macOS

1. **Install Qt6**
   ```bash
   brew install qt6
   ```

2. **Install CMake**
   ```bash
   brew install cmake
   ```

3. **Build**
   ```bash
   cd CrossWordQuest_Desktop
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   cmake --build .
   ```

4. **Run**
   ```bash
   ./bin/CrossWordQuestAuth
   ```

#### Linux (Ubuntu/Debian)

1. **Install Qt6**
   ```bash
   sudo apt-get update
   sudo apt-get install qt6-base-dev qt6-tools-dev
   ```

2. **Install CMake**
   ```bash
   sudo apt-get install cmake
   ```

3. **Build**
   ```bash
   cd CrossWordQuest_Desktop
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   cmake --build .
   ```

4. **Run**
   ```bash
   ./bin/CrossWordQuestAuth
   ```

### Using Qt Creator

1. Open Qt Creator
2. File → Open File or Project
3. Select `CMakeLists.txt`
4. Select kit (MSVC 2022 / Clang / GCC)
5. Click Configure Project
6. Build → Build All (Ctrl+Shift+B)
7. Run (Ctrl+R)

### Build Variables

Override CMake variables:
```bash
cmake .. \
  -DCMAKE_PREFIX_PATH=/path/to/qt6 \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER=g++
```

### Troubleshooting

**Qt not found**
```bash
# Find Qt installation
find /usr -name "qmake" 2>/dev/null

# Use correct path
cmake .. -DCMAKE_PREFIX_PATH=/usr/lib/qt6
```

**CMake not found**
- Windows: Add CMake to PATH or reinstall
- macOS: `brew install cmake`
- Linux: `sudo apt-get install cmake`

**Build fails with linking errors**
- Delete `build` directory and rebuild
- Update Qt to latest 6.x version
