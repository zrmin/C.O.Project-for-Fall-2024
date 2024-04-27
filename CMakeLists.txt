cmake_minimum_required(VERSION 3.29)

project(lc3bsim
	VERSION 1.0.0.0
	DESCRIPTION "C.O.Project for Fall 2024"
	LANGUAGES C CXX)

set(welcome "\t ${lc3bsim_DESCRIPTION}")

message(${lc3bsim_SOURCE_DIR})
message("\t\t\t\t ________________________________________")
message("\t\t\t\t|${welcome}\t |")
message("\t\t\t\t|________________________________________|")
message("\t\t\t\t|\t    Version: ${lc3bsim_VERSION}\t\t |")
message("\t\t\t\t|________________________________________|")

# 检查当前目录下是否存在名为 "coproject" 的文件
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/scripts/coproject")
    message(FATAL_ERROR "The file 'coproject' does not exist in the current directory.")
endif()

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(warmup Lab0/lab0.c)
add_executable(assembler Lab1/assembler.c)

foreach(lab_number RANGE 2 6)
  add_executable(lc3bsim${lab_number} "Lab${lab_number}/lc3bsim${lab_number}.c")
endforeach()

# 添加一个清理目标，用于删除构建文件
add_custom_target(cleanup
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/scripts/cleanup.cmake
  COMMENT "Cleaning up the build directory..."
)

# 创建一个 CMake 脚本以删除额外的构建文件
file(WRITE ${CMAKE_SOURCE_DIR}/scripts/cleanup.cmake
  "file(REMOVE_RECURSE
    \"CMakeCache.txt\"
    \"bin/\"
    \"lib/\"
    \"include/\"
  )"
)

# 定义一个宏，用于为每个 Lab 创建目标
macro(create_lab_target lab_number)
  add_custom_target(lab${lab_number}
	DEPENDS cleanup
	COMMAND ${CMAKE_COMMAND} ..
    	COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target assembler
    	COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target lc3bsim${lab_number}
    	COMMENT "Building lab${lab_number}..."
  )
endmacro()

add_custom_target(lab0
	DEPENDS cleanup
	COMMAND ${CMAKE_COMMAND} ..
	COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target warmup
	COMMENT "Building lab0..."
)
add_custom_target(lab1
	DEPENDS cleanup
	COMMAND ${CMAKE_COMMAND} ..
	COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target assembler
	COMMENT "Building lab1..."
)

# 使用宏为每个 Lab 创建目标
foreach(lab_number RANGE 2 6)
  create_lab_target(${lab_number})
endforeach()

add_custom_target(info
  COMMAND man -l ../scripts/coproject
  COMMENT "Displaying the manual page for C.O.Project"
)

add_custom_target(usage
  # 使用cmake -E 选项来执行echo命令，确保跨平台一致性
  COMMAND ${CMAKE_COMMAND} -E echo ""
  COMMAND ${CMAKE_COMMAND} -E echo "Usage: make [target]"
  COMMAND ${CMAKE_COMMAND} -E echo ""
  COMMAND ${CMAKE_COMMAND} -E echo "Available targets:"
  COMMAND ${CMAKE_COMMAND} -E echo "  info\t-  List C.O.Project overview"
  COMMAND ${CMAKE_COMMAND} -E echo "  lab0\t-  Build lab0 target `warmup`"
  COMMAND ${CMAKE_COMMAND} -E echo "  lab1\t-  Build lab1 target `assembler`"
  COMMAND ${CMAKE_COMMAND} -E echo "  lab2\t-  Build lab2 target `lc3bsim2`"
  COMMAND ${CMAKE_COMMAND} -E echo "  lab3\t-  Build lab3 target `lc3bsim3`"
  COMMAND ${CMAKE_COMMAND} -E echo "  lab4\t-  Build lab4 target `lc3bsim4`"
  COMMAND ${CMAKE_COMMAND} -E echo "  lab5\t-  Build lab5 target `lc3bsim5`"
  COMMAND ${CMAKE_COMMAND} -E echo "  lab6\t-  Build lab6 target `lc3bsim6`"

  COMMAND ${CMAKE_COMMAND} -E echo ""

  COMMAND ${CMAKE_COMMAND} -E echo "  usage\t- Show this message"
  DEPENDS ""
  # 确保'help'目标在默认构建时不被调用
  VERBATIM
)

# 设置help目标的属性，以排除在默认构建之外
set_target_properties(usage PROPERTIES
  EXCLUDE_FROM_ALL TRUE
  EXCLUDE_FROM_DEFAULT_BUILD TRUE
)
