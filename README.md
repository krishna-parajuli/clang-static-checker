### tl;&dr
once a clang build is generated,
```cd  path/to/build/```
```./bin/function-declaration path/to/test/file/test.cpp --``` works in 64-bit ubuntu 16.04 

pass any ```source file``` in place of ```test.cpp``` to statically analyze it  

### Screenshots
![running the tool in an errornous file](clangScreenshotErrorneousFile1.png?raw=true "running tool on an errornous file")


![running the tool in a working source file](clangScreenShot2.png?raw=true "running tool on a working source file")


## Installation

Following installation instruction are based on the official documentation at https://clang.llvm.org/docs/LibASTMatchersTutorial.html

###### getting clang llvm ninja cmake and installing requirements

```
mkdir ~/clang-llvm && cd ~/clang-llvm
git clone http://llvm.org/git/llvm.git
cd llvm/tools
git clone http://llvm.org/git/clang.git
cd clang/tools
git clone http://llvm.org/git/clang-tools-extra.git extra

cd ~/clang-llvm
git clone https://github.com/martine/ninja.git
cd ninja
git checkout release
./bootstrap.py
sudo cp ninja /usr/bin/

cd ~/clang-llvm
git clone git://cmake.org/stage/cmake.git
cd cmake
git checkout next
./bootstrap
make
sudo make install
```

###### building clang

```
cd ~/clang-llvm
mkdir build && cd build
cmake -G Ninja ../llvm -DLLVM_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release # Enable tests; default is off. to reduce build time use release flag
ninja
ninja check       # Test LLVM only.
ninja clang-test  # Test Clang only.
ninja install
```

## SetUP
###### making clang it's own compiler


```cd ~/clang-llvm/build
ccmake ../llvm
```

on the GUI set ```CMAKE_CXX_COMPILER``` to place pointed by ```which clang++``` also point respective path for ```CMAKE_C_COMPILER```

press ```c``` to configure and ```g``` to generate after setting the changes and run the command ```ninja```

###### registering your tool's directory in clang

```
cd ~/clang-llvm/llvm/tools/clang
mkdir tools/extra/function-declaration #set YOUR_DIRECTORY_NAME in place of function-declaration
echo 'add_subdirectory(function-declaration)' >> tools/extra/CMakeLists.txt
```

###### Making CMakeLists for your tool's directory

```
nano ~/clang-llvm/llvm/tools/clang/tools/extra/function-declaration/CMakeLists.txt
```
and copy the following into the text file

```
set(LLVM_LINK_COMPONENTS support)

add_clang_executable(function-declaration
  FunctionDeclarations.cpp
  )
target_link_libraries(function-declaration PRIVATE
  clangTooling
  clangBasic
  clangASTMatchers
  )
 ```

this will link required libraries and add your function to clang's executable.

## usage
now make new file ```FunctionDeclarations.cpp``` in the same directory and implement the tool functionality you would want clang to use, make sure subdirectory is <a href=#registering-your-tools-directory-in-clang>registered</a>

if any further changes are required reflect them in the respective ```CMakeLists.txt``` files

after changes are made run ```ninja``` command and
go to build folder of clang-llvm to run the following command and compile any source file with the clang changes you have made, (the executable of tool you have made will be availed at ```~/clang-llvm/build/bin/```)

###### compile a test file
```./bin/function-declaration test.cpp --```

