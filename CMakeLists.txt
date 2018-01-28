set(LLVM_LINK_COMPONENTS support)

add_clang_executable(function-declaration
  FunctionDeclarations.cpp
  )
target_link_libraries(function-declaration PRIVATE
  clangTooling
  clangBasic
  clangASTMatchers
  )
