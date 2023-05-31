cmake_minimum_required(VERSION 3.10)
project(automatasTP)


set(CMAKE_C_STANDARD 99)
set(TESTS_DIR ${automatasTP_SOURCE_DIR}/tests)
set(SRC_DIR ${automatasTP_SOURCE_DIR}/src)
set(TESTS_EXEC ${automatasTP_SOURCE_DIR}/tests/exec)


add_executable(automata ${SRC_DIR}/tp3.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(automata PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(automata PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${automatasTP_SOURCE_DIR}/src)

add_executable(test_afnd_to_afd ${TESTS_DIR}/test_afnd_to_afd.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_afnd_to_afd PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_afnd_to_afd PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_build_from_dot ${TESTS_DIR}/test_build_from_dot.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_build_from_dot PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_build_from_dot PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_build ${TESTS_DIR}/test_build.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_build PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_build PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_strings_pertains ${TESTS_DIR}/test_strings_pertains.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_strings_pertains PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_strings_pertains PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_pertains ${TESTS_DIR}/test_pertains.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_pertains PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_pertains PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_read_and_write ${TESTS_DIR}/test_read_and_write.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_read_and_write PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_read_and_write PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

