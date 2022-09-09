core_src_path='Core/Src/'
hal_src_path='Drivers/*/Src/'
core_src="$(find "$core_src_path" -type f -name '*.c' -o -name '*.cpp')"
hal_src="$(eval find "$hal_src_path" -type f -name '*.c')"

printf "$core_src\n$hal_src\n" > SOURCE.txt