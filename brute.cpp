#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "timer.hpp"

#include "key.hpp"
#include "brute.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;

Brute::Brute(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
}

void Brute::decrypt(const std::string& encrypted){
	// your code here
	Key encrypted_pw(encrypted);
	
	if(C == 4) {
		Key first("aaaa");
		Key last("5555");
		Key adder("aaab");	
		for(;first < last;first += adder){
			if(first.subset_sum(T, verbose) == encrypted_pw){
				first.show2();
			}
		}			
	}

	if(C == 5) {
		Key first("aaaaa");
		Key last("55555");
		Key adder("aaaab");	
		for(;first < last;first += adder){
			if(first.subset_sum(T, verbose) == encrypted_pw){
				first.show2();
			}
		}	
	}

	if(C == 6) {
		Key first("aaaaaa");
		Key last("555555");
		Key adder("aaaaab");

		for(;first < last;first += adder){
			if(first.subset_sum(T, verbose) == encrypted_pw){
				first.show2();
			}
		}			
	}

	
}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Brute force cracking of Subset-sum password with " 
		<< B << " bits precision\n"
	    << "USAGE: " << me << " <encrypted> <table file> [options]\n"
		<< "\nArguments:\n"
		<< " <encrypted>:   encrypted password to crack\n"
		<< " <table file>:  name of file containing the table to use\n"
		<< "\nOptions:\n"
		<< " -h|--help:     print this message\n"
		<< " -v|--verbose:  select verbose mode\n\n";
	exit(0);
}

void initialize(int argc, char* argv[]) {
	me = argv[0];
	if (argc < 3) usage("Missing arguments");
	encrypted = argv[1];
	table_filename = argv[2];
	for (int i=3; i<argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") usage();
		else if (arg == "-v" || arg == "--verbose") verbose = true;
		else usage("Unrecognized argument: " + arg);
	}
}


int main(int argc, char *argv[]){
	
	initialize(argc, argv);
	//CPU_timer t;
	//t.tic();
	Brute brute((std::string(argv[2])));
	brute.decrypt((std::string(argv[1])));
	//t.toc();
	//std::cout << "brute " << t.elapsed() << std::endl;	
	/*
	Key add("a555");
	Key addend("aaab");
	add += addend;
	Key sub("baaa");
	Key subtractend("baaa");
	sub -= subtractend;
	add.show2();
	sub.show2();
	*/
	return 0;
}
