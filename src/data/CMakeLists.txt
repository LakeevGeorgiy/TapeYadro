project(DataLayer)

add_library(${PROJECT_NAME}
    models/ConfigurationProperties.h 
    models/ConfigurationProperties.cpp 
    models/NecessaryFiles.h 
    models/NecessaryFiles.cpp
    services/CommandLineParser.h 
    services/CommandLineParser.cpp 
    services/EnvFileParser.h 
    services/EnvFileParser.cpp 
    services/Tape.h 
    services/Tape.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE DomainLayer)