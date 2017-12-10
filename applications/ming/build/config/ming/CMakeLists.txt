file(GLOB header_files
  ./../../../include/ming/*.hpp)
file(GLOB source_files
  ./../../../source/*.cpp)

add_executable(ming ${header_files} ${source_files})

set_source_files_properties(${header_files} PROPERTIES HEADER_FILE_ONLY TRUE)

install(TARGETS ming DESTINATION $ENV{INSTALL_DIRECTORY})
