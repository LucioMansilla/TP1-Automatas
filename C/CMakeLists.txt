cmake_minimum_required(VERSION 3.10)
project(automatasTP)


set(CMAKE_C_STANDARD 99)
set(TESTS_DIR ${automatasTP_SOURCE_DIR}/tests)
set(SRC_DIR ${automatasTP_SOURCE_DIR}/src)
set(TESTS_EXEC ${automatasTP_SOURCE_DIR}/tests/exec)



add_executable(automata ${SRC_DIR}/main.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
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

add_executable(test_strings_belongs ${TESTS_DIR}/test_strings_belongs.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_strings_belongs PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_strings_belongs PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_belongs ${TESTS_DIR}/test_belongs.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_belongs PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_belongs PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_read_and_write ${TESTS_DIR}/test_read_and_write.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_read_and_write PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_read_and_write PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_union ${TESTS_DIR}/test_union.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_union PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_union PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_concat ${TESTS_DIR}/test_concat.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_concat PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_concat PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_kleene ${TESTS_DIR}/test_kleene.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_kleene PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_kleene PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_tp1 ${TESTS_DIR}/test_tp1.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_tp1 PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_tp1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_tp2 ${TESTS_DIR}/test_tp2.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_tp2 PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_tp2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_minimize ${TESTS_DIR}/test_minimize.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_minimize PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_minimize PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)


add_executable(test_parser ${TESTS_DIR}/test_parser.c  ${SRC_DIR}/mini_grep.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_parser PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_parser PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)

add_executable(test_mini_grep ${TESTS_DIR}/test_mini_grep.c  ${SRC_DIR}/mini_grep.c ${SRC_DIR}/automata.c ${SRC_DIR}/utils.c ${SRC_DIR}/transition.c ${SRC_DIR}/linked_list.c)
target_include_directories(test_mini_grep PUBLIC ${automatasTP_SOURCE_DIR}/src)
set_target_properties(test_mini_grep PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_EXEC}/)