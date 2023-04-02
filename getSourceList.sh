#!/bin/bash

# Run .\getSourceList.sh in terminal to generate an updated list of source for CMake

APP_PATH='Application/*'
CORE_PATH='Core/*'
DRIVERS_PATH='Drivers/*'
FATFS_PATH='FATFS/*'
MIDWARE_PATH='Middlewares/*'
USB_PATH='USB_Device/*'

APP_SRC="$(eval find "$APP_PATH" -type f -name '*.c' -o -name '*.cpp' -o -name '*.s')"
CORE_SRC="$(eval find "$CORE_PATH" -type f -name '*.c' -o -name '*.cpp' -o -name '*.s')"
DRIVERS_SRC="$(eval find "$DRIVERS_PATH" -type f -name '*.c')"
FATFS_SRC="$(eval find "$FATFS_PATH" -type f -name '*.c')"
MIDWARE_SRC="$(eval find "$MIDWARE_PATH" -type f -name '*.c')"
USB_SRC="$(eval find "$USB_PATH" -type f -name '*.c')"

# Print find result
printf "$APP_SRC\n$CORE_SRC\n$DRIVERS_SRC\n$FATFS_SRC\n$USB_SRC\n$MIDWARE_SRC" > cmake/SourceList.cmake

# Total Scan Method Has bug
#ALL_SRC="$(eval find * ! -wholename 'build/*' -type f -name '*.c' -o -name '*.cpp' -o -name '*.s')"
#printf "$ALL_SRC" > test.txt


# Remove Empty Line
sed -i '/./!d' cmake/SourceList.cmake

# Adding ${PROJ_PATH}/ to beginning of each line
sed -i 's/^/${PROJ_PATH}\//' cmake/SourceList.cmake

# Struct cmake format
sed -i '1 i\set(source_list ${source_list}' cmake/SourceList.cmake
sed -i -e '$a)' cmake/SourceList.cmake