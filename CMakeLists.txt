# CMakeLists file

cmake_minimum_required (VERSION 3.22.1)
project (CONFIG_PARSER)

add_executable (configs_parser.out ./src/main.c ./src/input_and_output.c ./src/config_parsing_methods.c)
