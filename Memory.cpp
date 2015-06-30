#include "Memory.h"

	Memory::Memory(string user_prog, int addr,int val, bool set)
	{
		finish = 0; 
		string program = user_prog; 
		cout << "OPENING FILE : " << user_prog << endl; 
		address = addr; 
		value = val; 
		setting = set; 
		int instr;
                string unparsed;
                ifstream inputFile(program.c_str());
               	if(!inputFile)
                {
                        cout << "Error Reading File" << endl;
                }
                while(!inputFile.eof())
                {
                        getline(inputFile,unparsed);
			if (unparsed.length() == 0)
			{
				continue; 
			}
			instr = ret_instr(unparsed);
		        if(address == instr || instr == -1)
                        {					
                                continue;
                        }
                        memory[address] = instr;
			cout << "ADDRESS : " << address << " VALUE : " << memory[address] << endl; 
			address++;
			finish++; 
		}
		
		cout << endl; 

	}
int Memory::ret_instr(string parseIt)
{
        string instr;
        bool flag = true;
        int final;
        int start = 0;
        char check = parseIt[0];
        if (isspace(check))
	{
		return -1; 
	}
	if (check == '.')
        {
                flag = false;
                start = 1;
        }
        int end  = parseIt.find(" ");
        instr = parseIt.substr(start,end);
        istringstream convert(instr);
        convert >> final;
        if (flag == false)
        {
                address = final;
        }
                return final;
}
int Memory::read(int addr)
{
	value = memory[addr];
	return value;
}
void  Memory::write(int addr,int val)
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
bool Memory::end(int addr)
{
	if(addr < finish)
		return false;
	else if (addr == finish)
		return true;
}



