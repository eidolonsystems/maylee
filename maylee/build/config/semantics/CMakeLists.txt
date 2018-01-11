file(GLOB header_files ./../../../include/maylee/semantics/*.hpp)
file(GLOB source_files ./../../../source/semantics/*.cpp)
add_library(semantics ${header_files} ${source_files})
set_source_files_properties(${header_files} PROPERTIES HEADER_FILE_ONLY TRUE)
set_target_properties(semantics PROPERTIES
  STATIC_LIBRARY_FLAGS_RELEASE "${CMAKE_LIBRARY_FLAGS}"
  OUTPUT_NAME maylee_semantics)
install(TARGETS semantics CONFIGURATIONS Debug
  DESTINATION $ENV{LIB_INSTALL_DIRECTORY}/debug)
install(TARGETS semantics CONFIGURATIONS Release RelWithDebInfo
  DESTINATION $ENV{LIB_INSTALL_DIRECTORY}/release)

file(GLOB test_header_files ./../../../include/maylee/semantics_tester/*.hpp)
file(GLOB test_source_files ./../../../source/semantics_tester/*.cpp)
add_executable(semantics_tester ${test_header_files} ${test_source_files})
set_source_files_properties(${test_header_files}
  PROPERTIES HEADER_FILE_ONLY TRUE)
add_custom_command(TARGET semantics_tester POST_BUILD COMMAND semantics_tester)
install(TARGETS semantics_tester CONFIGURATIONS Debug
  DESTINATION $ENV{TEST_INSTALL_DIRECTORY}/debug)
install(TARGETS semantics_tester CONFIGURATIONS Release RelWithDebInfo
  DESTINATION $ENV{TEST_INSTALL_DIRECTORY}/release)
