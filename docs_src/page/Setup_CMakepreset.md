# Prepare CMakePresets.json file

`CMakePresets.json` provides definition for user configuration. Having this file allows developer to quickly change between debug and release mode.

- Release: `-O3 -DNDEBUG`
- Debug: `-O0 -g`
- RelWithDebInfo: `-O2 -g -DNDEBUG`
- MinSizeRel: `-Os -DNDEBUG`

- Create file `CMakePresets.json` in Project Root


> CMakePresets.json

```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "default",
      "hidden": true,
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build/${presetName}",
      "toolchainFile": "${sourceDir}/cmake/gcc-arm-none-eabi.cmake",
      "cacheVariables": {
      "CMAKE_EXPORT_COMPILE_COMMANDS": "ON"
      }
    },
    {
      "name": "Debug",
      "inherits": "default",
      "cacheVariables": {
      "CMAKE_BUILD_TYPE": "Debug"
      }
    },
    {
      "name": "RelWithDebInfo",
      "inherits": "default",
      "cacheVariables": {
      "CMAKE_BUILD_TYPE": "RelWithDebInfo"
      }
    },
    {
      "name": "Release",
      "inherits": "default",
      "cacheVariables": {
      "CMAKE_BUILD_TYPE": "Release"
      }
    },
    {
      "name": "MinSizeRel",
      "inherits": "default",
      "cacheVariables": {
      "CMAKE_BUILD_TYPE": "MinSizeRel"
      }
    }
  ]
}
```