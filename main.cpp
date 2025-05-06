#include <iostream>

#include "src/configuration/ConfigurationProperties.h"
#include "src/tape/Tape.h"
#include "src/parser/CommandLineParser.h"

int main(int argc, char* argv[]) {

	CommandLineParser parser;
	auto files = parser.ParseCommandLine(argc, argv);

	std::cout << "input file: " << files.input_file_path_ << "\n";
	std::cout << "output file: " << files.output_file_path_ << "\n";
	std::cout << "env file: " << files.env_file_path_ << "\n";

	try {

		ConfigurationProperties properties(files.input_file_path_, files.output_file_path_);
		properties.ParseEnvFile(files.env_file_path_);

		Tape tape(properties);
		tape.StartSorting();

	} catch (const std::exception& ex) {
		std::cout << ex.what() << "\n";
	}
	return 0;
}