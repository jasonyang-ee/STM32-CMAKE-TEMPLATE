#!/bin/bash

# Run .\getIncludeList.sh in terminal to generate an updated list of source for CMake

APP_PATH='Application/*'
DEP_LIB_PATH='Application/Inc/*'
CORE_PATH='Core/*'
DRIVERS_PATH='Drivers/*'
# FATFS_PATH='FATFS/*'
MIDWARE_PATH='Middlewares/*'
RTOS_PATH='Middlewares/Third_Party/FreeRTOS/*'
# USB_PATH='USB_Device/*'

# Clear the file
> cmake/IncludeList.cmake

if [ -n "$APP_PATH" ]; then
	APP_INC="$(eval find "$APP_PATH" -type d -name 'Inc')"
	printf "$APP_INC\n" >>cmake/IncludeList.cmake
fi

if [ -n "$DEP_LIB_PATH" ]; then
	DEP_LIB_INC="$(eval find "$DEP_LIB_PATH" -type d)"
	printf "$DEP_LIB_INC\n" >>cmake/IncludeList.cmake
fi

if [ -n "$CORE_PATH" ]; then
	CORE_INC="$(eval find "$CORE_PATH" -type d -name 'Inc' -o -name 'Include')"
	printf "$CORE_INC\n" >>cmake/IncludeList.cmake
fi

if [ -n "$DRIVERS_PATH" ]; then
	DRIVERS_INC="$(eval find "$DRIVERS_PATH" -type d -name 'Inc' -o -name 'Include' -o -name 'Legacy')"
	printf "$DRIVERS_INC\n" >>cmake/IncludeList.cmake
fi

if [ -n "$FATFS_PATH" ]; then
	FATFS_INC="$(eval find "$FATFS_PATH" -type d)"
	printf "$FATFS_INC\n" >>cmake/IncludeList.cmake
fi

if [ -n "$RTOS_PATH" ]; then
	RTOS_INC="$(eval find "$MIDWARE_PATH" -type d -name 'include' -o -name 'CMSIS_RTOS' -o -name 'ARM_CM4F')"
	printf "$RTOS_INC\n" >>cmake/IncludeList.cmake
fi

if [ -n "$MIDWARE_PATH" ]; then
	MIDWARE_INC="$(eval find "$MIDWARE_PATH" -type d -name 'Inc' -o -name 'src')"
	printf "$MIDWARE_INC\n" >>cmake/IncludeList.cmake
fi

if [ -n "$USB_PATH" ]; then
	USB_INC="$(eval find "$USB_PATH" -type d)"
	printf "$USB_INC\n" >>cmake/IncludeList.cmake
fi

# Remove Empty Line
sed -i '/./!d' cmake/IncludeList.cmake

# Adding ${PROJ_PATH}/ to beginning of each line
sed -i 's/^/${PROJ_PATH}\//' cmake/IncludeList.cmake

# Struct cmake format
sed -i '1 i\set(include_list ${include_list}' cmake/IncludeList.cmake
sed -i -e '$a)' cmake/IncludeList.cmake
