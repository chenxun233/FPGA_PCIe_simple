cmake_minimum_required(VERSION 3.10)
project(PCIe_transfer LANGUAGES C)

# Library target
add_library(PCIe_transfer
    src_c/src/PCIe_func.c
)
# Make the library's headers available to itself and dependents
target_include_directories(PCIe_transfer PUBLIC src_c/include)

# Main executable — define first
add_executable(PCIe_transfer_exec src_c/src/main.c)
# Then link the library to the executable
target_link_libraries(PCIe_transfer_exec PRIVATE PCIe_transfer)