project(DomainLayer)

add_library(${PROJECT_NAME}
    services/TapeInterface.h
    services/CommandLineParserInterface.h 
    services/EnvFileParserInterface.h 
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)