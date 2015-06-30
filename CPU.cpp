#include "CPU.h"

CPU::CPU(int time)
{
	IFLAG = false; 
	sys_mode = false;
	SFLAG = false; 
	PC = 0;
	AC = 0; 
	IR = 0;
	X = 0;
	Y = 0;
	SP = 999;
	OP = 0;	
	timer = time;
	on = true;
	interrupt = false; 
	stat = 0; 
	IC = 0;  
}				
void CPU::set_CPU(bool C_mode)
{
	on = C_mode; 
}
bool CPU::get_CPU()
{
	return on; 
}
void CPU::set_pc(int addr)
{
	PC = addr; 
}
void CPU::inc_pc()
{
	PC++;
}
void CPU::inc_sp()
{
	SP++;
}
void CPU::dec_pc()
{
	PC--; 
}
void CPU::dec_sp()
{
	SP--;
}
int CPU::get_pc()
{
	return PC; 
}
void CPU::set_ir(int val)
{
	IR = val; 
}
int CPU::get_ir()
{
	return IR;
}
void CPU::set_op(int val)
{
	OP = val; 
}
int CPU::get_op()
{
	return OP; 
}
int CPU::get_stat()
{
//	cout << "GET STAT : " << stat << endl; 
	return stat; 
}
void CPU::set_stat(int type)
{
	stat = type; 
}
void CPU::print_X()
{
//	cout << "X : " <<  X << endl;
}
void CPU::print_Y()
{
//	cout << "Y : " << Y << endl;
}
void CPU::print_ac()
{
//	cout << "AC : " << AC << endl; 
}
void CPU::execute(int instr, int op)
{
	IC++;
	if(IC%timer == 0 && interrupt == false)
	{
		IFLAG = true; 
		Int();  
		this->set_pc(1000); 
		sys_mode = true; 
	} 
	else if (IC%timer == 0 && interrupt == true)
	{
		while(interrupt)
		{
			if()
			
		} 
	}
	switch(instr)
	{
		case 1: Load_val(op);
			break;
		case 2: Load_addr(op);
			break;	
		case 3: Load_ind(op);
			break; 
		case 4: Load_idxX(op);
			break; 
		case 5: Load_idxY(op);
			break; 
		case 6:	Load_spX();
			this->set_ir(op);
			this->set_stat(1); 
			break; 
		case 8: {
				get();
//				cout << "CASE 8" << endl;
				this->set_ir(op);
				this->set_stat(1);
			}
			break;
		case 9: {
				put_port(op);
			}
			break; 
		case 10: {
				add_X();
//				cout << "CASE 10" << endl;
				this->set_ir(op);
				this->set_stat(1);
			}
			break;
		case 11: {
				add_Y();
//				cout << "CASE 11" << endl;
				this->set_ir(op);
				this->set_stat(1);
			}
			break; 
		case 12: {
				sub_X();
//				cout << "CASE 12" << endl;
				this->set_ir(op);
				this->set_stat(1);
			}
			break;
		case 13: {
				sub_Y();
//				cout << "CASE 13" << endl;
				this->set_ir(op);
				this->set_stat(1);
			}
			break; 
		case 14:{
				copy_to_X();
//				cout << "CASE 14" << endl;
				this->set_ir(op);
				this->set_stat(1);
			}
			break;
		case 15:{
				copy_from_X();
//				cout << "CASE 15" << endl;
				this->set_ir(op);
				this->set_stat(1);
			}
			break; 
		case 16:{
				copy_to_Y();
//				cout << "CASE 16" << endl;
				this->set_ir(op);
				this->set_stat(1);
			}
			break;
		case 17:{
				copy_from_Y();
				this->set_ir(op);
//				cout << "CASE 17" << endl;
				this->set_stat(1);
			}
			break; 
		case 18:{
				copy_to_SP();
//				cout << "CASE 18" << endl;
				this->set_ir(op);
				this->set_stat(1);
			}
			break;
		case 19:{
				copy_from_SP();
				this->set_ir(op);
//				cout << "CASE 19" << endl;
				this->set_stat(1);
			}
			break; 
		case 20:{
				jump(op);
			}
			break;
		case 21:{
				jump_if_equal(op);
			}
			break; 
		case 22:{
				jump_if_not_equal(op); 
			}
			break;
		case 23:{
				call_addr(op);
				SFLAG = false; 
//		cout << "CASE 23" << endl;
				this->set_stat(0); 
			}
			break; 
		case 24:{
				ret();
//				cout << "CASE 24" << endl;
			}
			break; 
		case 25:{
				inc_X();
				this->set_ir(op);
//				cout << "CASE 25" << endl;
				this->set_stat(1);
				
			}
			break;
		case 26:{
				dec_X();
				this->set_ir(op);
//				cout << "CASE 26" << endl;
				this->set_stat(1);
			}
			break;
		case 27:{
				push();
				this->set_ir(op);
//				cout << "CASE 27" << endl;
				this->set_stat(1);
			}
			break;
		case 28:{
				pop(); 
				this->set_ir(op);
//				cout << "CASE 28" << endl;
				this->set_stat(1);
			}
			break;
		case 29:{
				if(IFLAG == false)
				{
					Int();
					this->set_pc(1500);
				}else{
					while(IFLAG)
					{
						if(!this->get_iFlag())
						{
							Int();
							this->set_pc(1500); 
						}
					}
				}
			}
		case 30:{
				IRet();
			} 
		case 50:{
				this->set_stat(3);
			}		
	}
	
		
}
bool CPU::get_iFlag()
{
	return IFLAG; 
}
void CPU::Int()
{
	sys_mode = true; 
	this->store_pc(); 
	SP = 1999; 
	this->save_reg(); 
}
void CPU::save_reg()
{
	this->push();//save AC
	this->dec_sp();
	this->set_sp(IR);
	this->dec_sp();
	this->set_sp(X);
	this->dec_sp();
	this->set_sp(Y);
	 
}
void CPU::IRet()
{
	sys_mode = false;
	Y = this->get_sp();
	this->inc_sp();
	X = this->get_sp();
	this-> inc_sp();
	IR = this->get_sp();
	this-> inc_sp();
	AC = this->get_sp(); 
	this->inc_sp();
	SP = 999;
	PC = this->get_sp(); 
	this->inc_sp();
}
int CPU::get_sp()
{
	int pointed = stack[SP]; 
	cout << "Stack Location: " << SP << endl;
	cout << "Stack Content: " << stack[SP]<<endl; 
	cout << "POPPING: " << pointed << endl; 
	return pointed; 
}
void CPU::set_sp(int val)
{
	stack[SP] = val;
	cout << "Stack Location: " << SP << endl;
	cout << "Stack Content: " << stack[SP]<<endl; 
	cout << "PUSHING: " << val << endl; 
}

void CPU::Load_val(int op)
{
	AC = op;				
	cout << "LOADING VALUE: " << op << " INTO AC" <<endl; 
	this->print_ac();
//	cout << "CASE 1" << endl;
	this->set_stat(0); 
}
void CPU::Load_addr(int addr)
{
	this->store_pc(); 
	this->set_pc(addr);
	this->set_ir(1);  
//	cout << "CASE 2" << endl;
	this->set_stat(1);
}
void CPU::store_pc()
{
	this->set_sp(PC);
	this->dec_sp(); 
	SFLAG = true; 
}
void CPU::restore_pc()
{	
	PC = this->get_sp();
	this->inc_sp(); 
	SFLAG = false; 
}
bool CPU::get_flag()
{
	return SFLAG; 
}
void CPU::Load_ind(int addr)
{
	this->store_pc(); 
	this->set_pc(addr);
	this->set_ir(1); 
//	cout << "CASE 3" << endl;
	this->set_stat(1);
}
void CPU::Load_idxX(int addr)
{
	this->store_pc(); 
	PC = addr + X;
	this->set_ir(1);  
	//cout << "CASE 4" << endl;
	this->set_stat(1); 
}
void CPU::Load_idxY(int addr)
{
	this->store_pc(); 
	PC = addr + Y;
	this->set_ir(1); 
	//cout << "CASE 5" << endl;
	this->set_stat(1);
}
void CPU::push()
{
	this->dec_sp();
	this->set_sp(AC); 
}
void CPU::pop()
{
	AC = this->get_sp();
	this->inc_sp();
	this->print_ac();  
}
void CPU::inc_X()
{
	X++;
	this->print_X();
}
void CPU::dec_X()
{
	X--;
	this->print_X();
}

void CPU::ret()
{
	this->restore_pc(); 
	jump(PC); 
}
void CPU::call_addr(int addr)
{
	this->store_pc(); 
	jump(addr); 
}
void CPU::put_port(int op)
{
	if (op ==1)
	{
		cout << AC; 
	}
	else if (op == 2)
	{
		cout << (char)AC;
	}
//	cout << "CASE 9" << endl;
	this->set_stat(0); 
}
void CPU::jump(int addr)
{
		this->set_pc(addr); 
//		cout << "CASE 20" << endl;
		this->set_stat(0);
}
void CPU::jump_if_not_equal(int addr)
{
	this->print_ac(); 
	if (AC != 0)
	{
		this->set_pc(addr);
		this->set_stat(1);  
	}
//	cout << "CASE 22" << endl;
	this->set_stat(0); 
}
void CPU::jump_if_equal(int addr)
{
	this->print_ac(); 
	if (AC == 0)
	{
		this->set_pc(addr); 
	//	cout << "CASE 21" << endl;
		this->set_stat(0); 
	}
	else
	{
		this->set_stat(0); 
	}
}
void CPU::copy_to_SP()
{
	this->set_sp(AC);
	this->dec_sp();
}
void CPU::copy_from_SP()
{
	AC = this->get_sp(); 
	this->print_ac();
}
void CPU::copy_to_X()
{
	X = AC;
	this->print_X();
}
void CPU::copy_from_X()
{
	AC = X; 
	this->print_ac();
}
void CPU::copy_to_Y()
{
	Y = AC;
	this->print_Y();
}
void CPU::copy_from_Y()
{
	AC = Y; 
	this->print_ac();
}
void CPU::sub_X()
{
	AC -= X; 
	this->print_ac();
}
void CPU::sub_Y()
{
	AC -= Y;
	this->print_ac(); 
}
void CPU::add_X()
{
	AC += X; 
	this->print_ac(); 
}
void CPU::add_Y()
{
	AC += Y;
	this->print_ac(); 
}
void CPU::get()
{
	AC = rand() % 100 + 1; 
	this->print_ac(); 
}
void CPU::Load_spX()
{
	int address;
	this->inc_sp(); 
	AC = this->get_sp() + X;
	this->dec_sp(); 
	this->print_ac(); 
	//cout << "CASE 6" << endl;
}
	
