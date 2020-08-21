file(GLOB sources "*.cpp")

add_compile_definitions(RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

set(CMAKE_CXX_STANDARD 17)

foreach(src ${sources})
	get_filename_component(TARGET ${src} NAME_WLE)
	message(STATUS "${TARGET} added")
	add_executable(${TARGET} ${src})
	add_test(${TARGET}_test ${TARGET})
	target_link_libraries(${TARGET}  ${PODOFO_LIB} src)
endforeach()