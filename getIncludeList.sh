#!/bin/bash

# Run .\getIncludeList.sh in terminal to generate an updated list of source for CMake

APP_PATH='Application/*'
DEP_LIB_PATH='Application/Inc/*'
CORE_PATH='Core/*'
DRIVERS_PATH='Drivers/*'
FATFS_PATH='FATFS/*'
MIDWARE_PATH='Middlewares/*'
RTOS='Middlewares/Third_Party/FreeRTOS/*'
USB_PATH='USB_Device/*'

APP_INC="$(eval find "$APP_PATH" -type d -name 'Inc')"
DEP_LIB_INC="$(eval find "$DEP_LIB_PATH" -type d)"
CORE_INC="$(eval find "$CORE_PATH" -type d -name 'Inc' -o -name 'Include')"
DRIVERS_INC="$(eval find "$DRIVERS_PATH" -type d -name 'Inc' -o -name 'Include' -o -name 'Legacy')"
RTOS="$(eval find "$MIDWARE_PATH" -type d -name 'include' -o -name 'CMSIS_RTOS' -o -name 'ARM_CM4F')"
MIDWARE_INC="$(eval find "$MIDWARE_PATH" -type d -name 'Inc' -o -name 'src')"
USB_INC="$(eval find "$USB_PATH" -type d)"
FATFS_INC="$(eval find "$FATFS_PATH" -type d)"

# Print find result
printf "$APP_INC\n$DEP_LIB_INC\n$CORE_INC\n$DRIVERS_INC\n$RTOS\n$MIDWARE_INC\n$USB_INC\n$FATFS_INC" > cmake/IncludeList.cmake

# Remove Empty Line
sed -i '/./!d' cmake/IncludeList.cmake

# Adding ${PROJ_PATH}/ to beginning of each line
sed -i 's/^/${PROJ_PATH}\//' cmake/IncludeList.cmake

# Struct cmake format
sed -i '1 i\set(include_list ${include_list}' cmake/IncludeList.cmake
sed -i -e '$a)' cmake/IncludeList.cmake