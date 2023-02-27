#!/bin/bash

# Run .\getIncludeList.sh in terminal to generate an updated list of source for CMake

CORE_PATH='Core/*'
DRIVERS_PATH='Drivers/*'
FATFS_PATH='FATFS/*'
MIDWARE_PATH='Middlewares/*'
USB_PATH='USB_Device/*'

CORE_INC="$(eval find "$CORE_PATH" -type d -name 'Inc' -o -name 'Include')"
DRIVERS_INC="$(eval find "$DRIVERS_PATH" -type d -name 'Inc' -o -name 'Include' -o -name 'Legacy')"
FATFS_INC="$(eval find "$FATFS_PATH" -type d)"
MIDWARE_INC="$(eval find "$MIDWARE_PATH" -type d -name 'Inc' -o -name 'src')"
USB_INC="$(eval find "$USB_PATH" -type d)"

# Print find result
printf "$CORE_INC\n$DRIVERS_INC\n$FATFS_INC\n$MIDWARE_INC\n$USB_INC" > cmake/IncludeList.txt

# Adding ${PROJ_PATH}/ to beginning of each line
sed -i 's/^/${PROJ_PATH}\//' cmake/IncludeList.txt