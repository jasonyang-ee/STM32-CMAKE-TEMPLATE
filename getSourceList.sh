#!/bin/bash

# Run .\getSourceList.sh in terminal to generate an updated list of source for CMake

CORE_PATH='Core/*'
DRIVERS_PATH='Drivers/*'
FATFS_PATH='FATFS/*'
MIDWARE_PATH='Middlewares/*'
USB_PATH='USB_Device/*'

CORE_SRC="$(eval find "$CORE_PATH" -type f -name '*.c' -o -name '*.cpp' -o -name '*.s')"
DRIVERS_SRC="$(eval find "$DRIVERS_PATH" -type f -name '*.c')"
FATFS_SRC="$(eval find "$FATFS_PATH" -type f -name '*.c')"
MIDWARE_SRC="$(eval find "$MIDWARE_PATH" -type f -name '*.c')"
USB_SRC="$(eval find "$USB_PATH" -type f -name '*.c')"

# Print find result
printf "$CORE_SRC\n$DRIVERS_SRC\n$FATFS_SRC\n$USB_SRC\n$MIDWARE_SRC" > cmake/SourceList.txt

# Has bug
#ALL_SRC="$(eval find * ! -wholename 'build/*' -type f -name '*.c' -o -name '*.cpp' -o -name '*.s')"
#printf "$ALL_SRC" > test.txt

# Adding ${PROJ_PATH}/ to beginning of each line
sed -i 's/^/${PROJ_PATH}\//' cmake/SourceList.txt