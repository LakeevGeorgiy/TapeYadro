#include <iostream>
#include <memory>

#include "src/data/services/Tape.h"
#include "src/data/services/CommandLineParser.h"
#include "src/data/services/EnvFileParser.h"

int main(int argc, char* argv[]) {

	
	try {

		CommandLineParser arg_parser;
		auto files = arg_parser.ParseCommandLine(argc, argv);

		auto env_parser = std::make_shared<EnvFileParser>();
		Tape tape(env_parser);
		
		tape.SetUpTape(files.env_file_path_);
		tape.SortFile(files.input_file_path_, files.output_file_path_);

	} catch (const std::exception& ex) {
		std::cout << ex.what() << "\n";
	}
	return 0;
}