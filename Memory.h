#ifndef MEMORY_H
#define MEMORY_H        
#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <ctype.h> 

using namespace std;

class Memory
{
        private:
		int memory[2000];
		int address;
		int value;
		bool setting;
		int finish; 
	public:				
		Memory(string user_prog, int addr,int val,bool set);
		int read(int addr);
		void write(int addr,int val);
		void set_mode(bool set); 
		bool get_mode(); 
		int ret_instr(string parseIt);
		bool done(int addr); 
};
#endif 
