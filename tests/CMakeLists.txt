add_executable(sandwich_tests main.c sandwich_tests.c)
target_link_libraries(sandwich_tests ${LIBS} libsandwich)

add_test(SandwichTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sandwich_tests)

