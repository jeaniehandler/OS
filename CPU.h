#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string> 
#include <stdlib.h>
 
using namespace std; 

class CPU
{
	private:
		bool IFLAG; 
		int PC;
		int IR; 
		int X;
		int Y;
		int SP;
		int OP; 
		int timer;
		int AC; 
		bool on;
		bool interrupt;
		int stat; 	
		int stack[2000];		
		int IC; 
		bool SFLAG; 
		bool sys_mode; 

	public:
		void Int();
		void IRet();
		void save_reg();
		void dec_pc();
		bool get_flag(); 
		void store_pc();
		void restore_pc(); 
		int get_sp(); 
		void call_addr(int addr);
		void ret(); 
		void inc_X();
		void dec_X();
		void push();
		void pop(); 
		void put_port(int op);
		CPU(int time);
		void set_CPU(bool C_mode); 		
		bool get_CPU();
		void set_pc(int addr); 
		void inc_pc();
		int get_pc();
		void set_ir(int val);
		int get_ir();
		void set_op(int val);
		int get_op();
		void set_stat(int type);
		int get_stat();
		void execute(int instr,int op);
		void Load_val(int op);
		void Load_addr(int addr);
		void set_sp(int val); 
		void print_ac();
		void Load_ind(int addr);
		void Load_idxX(int addr);
		void Load_idxY(int addr);
		void Load_spX();
		void get(); 	
		void add_X();
		void add_Y();
		void copy_to_X();
		void copy_from_Y();
		void copy_to_Y();
		void copy_from_X();
		void copy_to_SP();
		void copy_from_SP();
		void sub_X();
		void sub_Y();
		void jump(int addr);
		void jump_if_not_equal(int addr);
		void jump_if_equal(int addr);
		void print_X();
		void print_Y();
		void inc_sp();
		void dec_sp(); 
		bool get_iFlag(); 
};
#endif
