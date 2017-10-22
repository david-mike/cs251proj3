#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "key.hpp"
#include "symbol.hpp"
#include "timer.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;


Symbol::Symbol(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
	

	std::string initial = "";
	
	for (int i = 0; i < C; i++) {
		initial += "a";
	}
	Key first(initial);
	std::string addStr = initial;
	addStr[addStr.length() - 1] = 'b';
	
	Key addend(addStr);
	
	//first.show2();
	//addend.show2();
	int stSize = (int)pow(2, C/2*B);
	
	for (int i = 0; i < stSize; i++) {
		Key sum = first.subset_sum(T, verbose);
		std::map<Key, std::vector<Key>>::iterator it;
		it = M.find(sum);
		if (it != M.end()) {
			M[sum].push_back(first);
			//std::cout<<1<<std::endl;
		} else {
			std::vector<Key> tempVector;
			tempVector.push_back(first);
			M.insert(std::pair<Key, std::vector<Key>>(sum, tempVector));
			//std::cout<<2<<std::endl;
		}
		first += addend;
		//first.show2();
	}
	/*
	int count = 0;
	for (std::map<Key, std::vector<Key>>::iterator it = M.begin(); it != M.end(); it++) {
		for (int i = 0; i < it->second.size(); i++) {
			it->second[i].show2();
			count++;	
		}
	}
	std::cout << count << std::endl;
	*/
}


void Symbol::decrypt(const std::string& encrypted){

	// insert your code here
	Key encrypted_key(encrypted);
	int length = C - C/2;
	std::string initial = "";
	std::string last = "";
	
	for (int i = 0; i < C; i++) {
		initial += "a";
	}

	std::string addStr = initial;

	for (int i = 0; i < length; i++) {
		last += "5";
	}
	for (int i = 0; i < C / 2; i++) {
		last += "a";	
	}

	addStr[addStr.length() - C / 2 - 1] = 'b';
	last[last.length() - 1] = 'b';

	Key begin(initial);
	Key end(last);
	Key addend(addStr);

	//begin.show2();
	//end.show2();
	//addend.show2();
	
	int stSize = (int)pow(2, (C - C/2) * B);
	//std::cout<< stSize<<std::endl;
	for (int i = 0 ; i < stSize; i++){
		//begin.show2();
		Key temp = encrypted_key;
		Key sum = begin.subset_sum(T, verbose);
		temp -= sum;
		std::map<Key, std::vector<Key>>::iterator it;
		it = M.find(temp);
		if (it != M.end()) {
			
			for (int j = 0; j!= it->second.size(); j++) {
				Key password = it->second[j];
				//password.show2();
				//std::cout<<j;
				password += begin;
			//	begin.show2();
				password.show2();
			}
		}
		begin += addend;
	}
}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Symbol table-based cracking of Subset-sum password"
		<< " with " << B << " bits precision\n"
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
	Symbol s = Symbol(argv[2]);
	s.decrypt(argv[1]);
	//t.toc();
	//std::cout << "Fast algorithm " << t.elapsed() << std::endl;

	return 0;
}
