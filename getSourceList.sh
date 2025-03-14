#!/bin/bash

# Run .\getSourceList.sh in terminal to generate an updated list of source for CMake

# Define the path to the source code
APP_PATH='Application/*'
CORE_PATH='Core/*'
DRIVERS_PATH='Drivers/*'
# FATFS_PATH='FATFS/*'
MIDWARE_PATH='Middlewares/*'
# USB_PATH='USB_Device/*'

# Clear the file
> cmake/SourceList.cmake

# Print find result
if [ -n "$APP_PATH" ]; then
	APP_SRC="$(eval find "$APP_PATH" -type f -name '*.c' -o -name '*.cpp' -o -name '*.s')"
	printf "$APP_SRC\n" >> cmake/SourceList.cmake
fi

if [ -n "$CORE_PATH" ]; then
	CORE_SRC="$(eval find "$CORE_PATH" -type f -name '*.c' -o -name '*.cpp' -o -name '*.s')"
	printf "$CORE_SRC\n" >> cmake/SourceList.cmake
fi

if [ -n "$DRIVERS_PATH" ]; then
	DRIVERS_SRC="$(eval find "$DRIVERS_PATH" -type f -name '*.c')"
	printf "$DRIVERS_SRC\n" >> cmake/SourceList.cmake
fi

if [ -n "$FATFS_PATH" ]; then
	FATFS_SRC="$(eval find "$FATFS_PATH" -type f -name '*.c')"
	printf "$FATFS_SRC\n" >> cmake/SourceList.cmake
fi

if [ -n "$MIDWARE_PATH" ]; then
	MIDWARE_SRC="$(eval find "$MIDWARE_PATH" -type f -name '*.c')"
	printf "$MIDWARE_SRC\n" >> cmake/SourceList.cmake
fi

if [ -n "$USB_PATH" ]; then
	USB_SRC="$(eval find "$USB_PATH" -type f -name '*.c')"
	printf "$USB_SRC\n" >> cmake/SourceList.cmake
fi

# Remove Empty Line
sed -i '/./!d' cmake/IncludeList.cmake

# Adding ${PROJ_PATH}/ to beginning of each line
sed -i 's/^/${PROJ_PATH}\//' cmake/SourceList.cmake

# Struct cmake format
sed -i '1 i\set(source_list ${source_list}' cmake/SourceList.cmake
sed -i -e '$a)' cmake/SourceList.cmake
