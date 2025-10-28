#--------------------------------------------------------------------------
# lab3 project
#--------------------------------------------------------------------------

PROJECT(lab5)
FILE(GLOB lab5_headers code/*.h *.hpp *.jpg *.obj *.gltf *.glb)
FILE(GLOB lab5_sources code/*.cc resources/*.vs resources/*.fs )

SET(files_lab5 ${lab5_headers} ${lab5_sources})
SOURCE_GROUP("lab5" FILES ${files_lab5})

ADD_EXECUTABLE(lab5 ${files_lab5})
TARGET_LINK_LIBRARIES(lab5 core render glm)
ADD_DEPENDENCIES(lab5 core render glm)
add_custom_command(
    TARGET lab5 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/
    ${CMAKE_SOURCE_DIR}/bin/resources/
)

set_target_properties(lab5 PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
