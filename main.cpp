#include <iostream>

#include "src/tape/Tape.h"
#include "src/parser/CommandLineParser.h"
#include "src/parser/EnvFileParser.h"

int main(int argc, char* argv[]) {

	
	try {

		CommandLineParser arg_parser;
		auto files = arg_parser.ParseCommandLine(argc, argv);
	
		std::cout << "input file: " << files.input_file_path_ << "\n";
		std::cout << "output file: " << files.output_file_path_ << "\n";
		std::cout << "env file: " << files.env_file_path_ << "\n";

		Tape tape;
		tape.SetUpTape(files.env_file_path_);
		tape.SortFile(files.input_file_path_, files.output_file_path_);

	} catch (const std::exception& ex) {
		std::cout << ex.what() << "\n";
	}
	return 0;
}