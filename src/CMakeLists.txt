add_library(libsandwich STATIC sandwich.c)

add_executable(sandwiches main.c)
target_link_libraries(sandwiches libsandwich ${LIBS})
