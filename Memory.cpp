#include "Memory.h"

	Memory::Memory(string user_prog, int addr,int val, bool set)
	{	
		finish = 0; 
		string program = user_prog; //user program passed as a string
		cout << "OPENING FILE : " << user_prog << endl; //test output to ensure proper string was passed
		address = addr; 
		value = val; 
		setting = set; 
		int instr;
		char check; 
                string unparsed;
                ifstream inputFile(program.c_str());
               	if(!inputFile)
                {
                        cout << "Error Reading File" << endl;
                }
                while(!inputFile.eof())
                {					
                        getline(inputFile,unparsed);//get first line of file and set as string unparsed
        		check = unparsed[0];//check = fst_char of string unparsed
			if (unparsed.length() == 0)//condition testing if string length equal to zero
			{
				continue; //read next line in file
			}
			instr = ret_instr(unparsed);//send string unparsed to function ret_instr to parse string into integer
		        if(address == instr  && check == '.' || instr == -1)//multiple checks to see if instruction is address
//might be repetitive
                        {					
                                continue;
                        }
                        memory[address] = instr;//memory array at address value saves the instruction 
			cout << "ADDRESS : " << address << " VALUE : " << memory[address] << endl; 
			address++;//increment address before reading nextline in file
		}
		
		cout << endl; 

	}
int Memory::ret_instr(string parseIt)
{
        bool flag = true;
        string instr;
        int final;
        int start = 0;
        char check = parseIt[0];//check == fst_char
        if (isspace(check))
	{
		return -1; //if fst_char is a space then return -1
	}
	if (check == '.')//if fst_char is a '.' set flag to false and start read at char[1] 
        {
                flag = false;
                start = 1;
        }
        int end  = parseIt.find(" ");//the end of a file line is an empty string //find function will return the end position
        instr = parseIt.substr(start,end);//the final parsed instruction is returned as a substring
        istringstream convert(instr);//convert the string into an integer value
        convert >> final;
        if (flag == false)//if flag is set to false, set the address to final integer value
        {
                address = final;
        }
                return final;//return the integer value to be further processed 
}
int Memory::read(int addr)//read function for Memory
{
	value = memory[addr];
	return value;
}
void  Memory::write(int addr,int val)//write function for memory
{
	memory[addr] = val;  
}
void Memory::set_mode(bool set)
{
	setting = set; 

}
bool Memory::get_mode()
{
	return setting; 
}
bool Memory::done(int addr)
{
	int length = sizeof(memory)/sizeof(int);
	
	if (addr > length || addr < 0)
	{
		return true; 
	}	
	for (int i =0;i < length-1 ;i++)
	{
		if(addr == i)
		{
			return false; 
		}
	}
	return true; 
}




