#include <signal.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <iostream>
#include "CPU.h"
#include "Memory.h"

using namespace std;

int main(int argc,char* argv[])
{

	int C_M[2];
	int M_C[2];
	int timer = 0; 
	string program; 
	pid_t pid; 
				
	switch(argc)
	{
                case 1:
                        {
                                cout << "program not entered" << endl;
                                return 0;
                        }
                        break;
                case 2:
                        {
                                program = argv[1];
                                cout << "Program : " << program << endl;
                                cout << "Timer not set" << endl;
                        }
                        break;
                case 3:
                        {
                                program = argv[1];
				string time = argv[2];
				stringstream s(time); 
                                s >> timer;
                                cout << "Program : " << program << endl;
                                cout << "Timer : " << timer << endl;
                        }
                         break;
         }
	pipe(C_M);
	pipe(M_C);
	if ((pid = fork()) == 0)
        {
		bool on; 
		bool set = true; 
		int cpu = 0; 
       		int addr = 0;
        	int val = 0; 
		Memory Main(program,addr,val,set);
        	close(M_C[0]);
        	close(C_M[1]);
        	read(C_M[0],&on,sizeof(on));//first read statement
       		while (on)
       	 	{
			
			read(C_M[0],&cpu,sizeof(cpu));
			write(M_C[1],&cpu,sizeof(cpu));  
			while (cpu > 0)
			{
				
                		read(C_M[0],&set,sizeof(set));
				Main.set_mode(set); 			
				if(Main.get_mode() == true)    
	                    	{	
			//		cout << "IN READ" << endl;	
                                	read(C_M[0],&addr,sizeof(addr));
					bool done = Main.end(addr);
					if(done)
					{
						val = -1; 
			//			cout << "end of File" << endl;
                                		write(M_C[1],&val,sizeof(val));
						cpu = 0; 
							
					}
					else
					{
						val = Main.read(addr);
                                		write(M_C[1],&val,sizeof(val));
						cpu = -1;				 	
					}
				}
                        	if (Main.get_mode() == false)
                        	{
                       	  //      cout << "IN WRITE" << endl; 
					read(C_M[0],&addr, sizeof(addr));
					read(C_M[0],&val, sizeof(val));
					Main.write(addr,val); 
					cpu = -1; 
			 	}	
       	 
				if(cpu == 0)
				{
					read(C_M[0],&on,sizeof(on));
			//		cout << "MEM OFF" <<endl; 
					close(M_C[1]);
					close(C_M[0]);
					kill(pid,SIGKILL); 
				}
			}
		}
		
	}
        else if (pid > 0)
        {
		int ready; 
		bool start = true; 
		bool mode; 
        	CPU OS(timer);
		int pc; 
		int retrieved; 
		int stat;
        	close(M_C[1]);
        	close(C_M[0]);
		write(C_M[1],&start,sizeof(start));//first write statement
        	while (OS.get_CPU())
        	{
			stat = OS.get_stat(); 
			if(stat == 0)//Retrieve Instr
                	{
				cout << "IN STAT 0" << endl;
				ready = 1; 
				write(C_M[1],&ready,sizeof(ready));
				read(M_C[0],&ready,sizeof(ready));
				if(ready)
				{
					mode = true; 	
					pc = OS.get_pc();
					write(C_M[1],&mode,sizeof(mode));
					write(C_M[1],&pc, sizeof(pc));	
					read(M_C[0],&retrieved, sizeof(retrieved));
					cout << "PC SENT : " << pc << " MEMORY RETURNS : " << retrieved << endl;
					if(retrieved == -1)
					{
						OS.set_stat(3);
						continue;
					}
					OS.set_ir(retrieved);
					OS.set_stat(1);
					OS.inc_pc();
				}
				continue; 
			}
			if(stat == 1)//Retrieve Op
			{
				cout << "IN STAT 1" << endl; 
				ready = 1; 
				write(C_M[1],&ready,sizeof(ready));
				read(M_C[0],&ready,sizeof(ready));
				if(ready)
				{
					mode = true; 
					pc = OS.get_pc(); 	
					write(C_M[1],&mode,sizeof(mode));
					write(C_M[1],&pc,sizeof(pc));
					read(M_C[0],&retrieved,sizeof(retrieved));
					cout << "ADDR SENT : " << pc << " MEMORY RETURNS : " << retrieved << endl;
					if(retrieved == -1)
					{
						OS.set_stat(3);
						continue;
					}
					OS.set_op(retrieved);
					OS.set_stat(2);
					OS.inc_pc(); 
				}
				continue; 
			}
			if(stat == 2)//Execute
			{
		cout << "IN STAT 2" << endl; 
				ready = -1; 
				write(C_M[1],&ready,sizeof(ready));
				read(M_C[0],&ready,sizeof(ready));
				if(ready == -1)
				{
					cout << "EXECUTE" << endl;
				cout << "INSTR : " << OS.get_ir() << " OP : " << OS.get_op() << endl;
						OS.execute(OS.get_ir(),OS.get_op()); 
						cout << endl;
					if(OS.get_stat() == 1)
					{
						continue; 
					}
					if(OS.get_flag() == true)
					{
						OS.set_stat(4); 		  
					}
					if(OS.get_ir() > 28)
					{
						OS.set_stat(3); 
					}
					continue; 
				}
			}
			if(stat == 3)
			{
				ready = 0; 
				write(C_M[1],&ready,sizeof(ready));
				read(M_C[0],&ready,sizeof(ready));
				if(!ready)
				{
					cout << "CPU OFF" << endl;
					start = false; 
					write(C_M[1],&start,sizeof(start));
					close(C_M[1]);
					close(M_C[0]);
					OS.set_CPU(false);
					kill(pid,SIGKILL); 
				}
			}
			if(stat == 4)
			{
				cout << "IN STAT 4" << endl; 
					OS.restore_pc();
					OS.set_stat(0); 
					continue; 
			}
		}
	
	}
	else
	{
               cout << "Error in Fork" << endl;
	}

return 0;
}
