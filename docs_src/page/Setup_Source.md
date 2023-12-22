# Prepare Source List and Include List file

Project source and include list are required for CMake to build the project.

This list includes HAL library and user source files.

The list is saved in `/cmake` folder.

The format of the list must be full path.

> SourceList.cmake

```cmake
set(source_list ${source_list}
${PROJ_PATH}/Application/Src/main.cpp
${PROJ_PATH}/Core/Src/stm32l4xx_hal_msp.c
${PROJ_PATH}/Core/Src/stm32l4xx_it.c
${PROJ_PATH}/Core/Src/syscalls.c
${PROJ_PATH}/Core/Src/system_stm32l4xx.c
${PROJ_PATH}/Core/startup_stm32l432kcux.s
)
```

> IncludeList.cmake

```cmake
set(include_list ${include_list}
${PROJ_PATH}/Application/Inc
${PROJ_PATH}/Core/Inc
)
```


# Auto Scan Source and Include List

Auto scan bash script has been made for STM32CubeMX generated files structure

- In terminal `` Ctrl + ` ``, run `.\getIncludeList.sh` and `.\getSourceList.sh`

- A list of scanned source and header will be saved in `/cmake` folder.

> You may modify bash file to expend the auto file searching for more folders.

> The bash simply scan `.c` `.cpp` `.s` file for source. And, it scan `/Inc` `/Include` for include path.