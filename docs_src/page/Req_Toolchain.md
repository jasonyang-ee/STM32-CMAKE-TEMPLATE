# Toolchain

- Download and prepare binary of each toolchain files in a centralized folder.

- Edit environment varialbe PATH to include those folder or it's `/bin` folder.

- ST Link tools are obtained by installing STM32CCubeIDE. Then, you will be able to find it in the installaiton folder.

![path](img/path.png)

# Essential Toolchain:

1. [ARM GNU](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

2. [CMake](https://cmake.org/download/)

3. [Ninja](https://github.com/ninja-build/ninja/releases)

4. ST Link GDB Server (From CubeIDE Installation).

   Example Location:

   `C:\ST\STM32CubeIDE_$YOUR_VERSION_NUMBER$\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.win32_2.0.100.202109301221`

5. STM32_Programmer_CLI (From CubeIDE Installation)
   
   Example Location:
   
   `C:\ST\STM32CubeIDE_$YOUR_VERSION_NUMBER$\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.win32_2.0.100.202110141430`


6. _Side Note: ST Link for Linux https://github.com/stlink-org/stlink_


# Test Your Toolchain Installation:

Run below commands in CMD to check toolchain installation.
```
arm-none-eabi-gcc --version
STM32_Programmer_CLI --version
ST-LINK_gdbserver --version
cmake --version
ninja --version
```
