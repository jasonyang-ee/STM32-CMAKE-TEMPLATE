# Setting Up VS Code to Build STM32 Using CMake

## Toolchain

Download and place those in a centralized folder. Edit environment PATH for those folder or it's bin folder.

- ARM GNU for compile
> https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
- CMake for easy execution of compile
> https://cmake.org/download/
- Ninja
> https://github.com/ninja-build/ninja/releases
- ST Link from Installing STM32CubeIDE
> c:\ST\STM32CubeIDE_$YOUR_VERSION_NUMBER$\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.win32_2.0.100.202109301221
- STM32_Programmer_CLI
> c:\ST\STM32CubeIDE_$YOUR_VERSION_NUMBER$\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.win32_2.0.100.202110141430

Run CMD to check toolchain installation.

```
arm-none-eabi-gcc --version
STM32_Programmer_CLI --version
ST-LINK_gdbserver --version
cmake --version
ninja --version
```