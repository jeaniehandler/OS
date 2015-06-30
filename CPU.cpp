#include "CPU.h"

CPU::CPU(int time)//CPU recieves timer interrupt option
{
	WAIT = false; 		
	IFLAG = 0; 
	sys_mode = false;
	SFLAG = false; 
	FP = 900; 
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
void CPU::set_iFlag(int set)
{
	IFLAG = set; 
}		
void CPU::set_CPU(bool C_mode)//turn CPU on
{
	on = C_mode; 
}
void CPU::set_pc(int addr)//initialize program counter
{
	PC = addr; 
}
void CPU::set_ir(int val)//pass instruction to instruction register
{
	IR = val; 
}
void CPU::set_op(int val)//set operand value
{
	OP = val; 
}
void CPU::set_stat(int type)
{
	stat = type; 
}
void CPU::set_next(int op)
{
	this->set_ir(op);
	this->set_stat(1);
}
void CPU::set_sp(int val)
{
//	cout << "SETTING" <<endl;
	stack[SP] = val;
//	cout << "Stack Location: " << SP << endl;
//	cout << "Stack Content: " << stack[SP]<<endl; 
}
void CPU::set_fp(int addr)
{
	stack[FP] = addr;
	FP+=1;
}
int CPU::get_iFlag()
{
	return IFLAG; 
}
bool CPU::get_CPU()
{
	return on; 
}
int CPU::get_pc()
{
	return PC; 
}
int CPU::get_ir()
{
	return IR;
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
int CPU::get_sp()
{
//	cout << "GETTING" <<endl; 
//	cout << "Stack Location: " << SP << endl;
//	cout << "Stack Content: " << stack[SP]<<endl; 
	return stack[SP]; 
}
int CPU::get_fp()
{
	FP-=1; 
	return stack[FP];
}
bool CPU::get_sFlag()
{
	return SFLAG; 
}
int CPU::get_ac()
{
	return AC; 
}
void CPU::inc_pc()
{
	PC+=1;
}
void CPU::dec_pc()
{
	PC-=1; 
}
void CPU::inc_sp()
{
//	cout << "POPPING " << endl; 
	SP+=1;
}
void CPU::dec_sp()
{

//	cout << "PUSHING " << endl; 
	SP-=1;
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
	if(interrupt == false)
	{
		IC++;
	}
//	cout << IC << endl; 
//	cout << IC%timer << endl; 
	if(IC%timer == 0 && interrupt == false && WAIT == false)
	{
		this->set_iFlag(1);
	}								 
	if(interrupt == false && IC%timer == 0 && this->get_iFlag() == 1)
	{
			interrupt = true;
			instr = -1; 
	}								
	if (interrupt == true && IC%timer ==0 && this->get_iFlag() == 0) 
	{		WAIT = true; 		
			this->set_iFlag(1);
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
			this->set_next(op);
			break;
		case 7: set_stat(5);
			this->save_last();
			break; 
		case 8: {
				get();
				this->set_next(op);
//				cout << "CASE 8" << endl;
			}
			break;
		case 9: {
				put_port(op);
			}
			break; 
		case 10: {
				add_X();
				this->set_next(op);
//				cout << "CASE 10" << endl;
			}
			break;
		case 11: {
				add_Y();
				this->set_next(op);
//				cout << "CASE 11" << endl;
			}
			break; 
		case 12: {
				sub_X();
				this->set_next(op);
//				cout << "CASE 12" << endl;
			}
			break;
		case 13: {
				sub_Y();
				this->set_next(op);
//				cout << "CASE 13" << endl;
			}
			break; 
		case 14:{
				copy_to_X();
				this->set_next(op);
//				cout << "CASE 14" << endl;
			}
			break;
		case 15:{
				copy_from_X();
				this->set_next(op);
//				cout << "CASE 15" << endl;
			}
			break; 
		case 16:{
				copy_to_Y();
				this->set_next(op);
//				cout << "CASE 16" << endl;
			}
			break;
		case 17:{
				copy_from_Y();
				this->set_next(op);
//				cout << "CASE 17" << endl;
			}
			break; 
		case 18:{
				copy_to_SP();
				this->set_next(op);
//				cout << "CASE 18" << endl;
			}
			break;
		case 19:{
				copy_from_SP();
				this->set_next(op);
//				cout << "CASE 19" << endl;
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
			//	this->set_stat(0); 
			}
			break; 
		case 24:{
				ret();
//				cout << "CASE 24" << endl;
			}
			break; 
		case 25:{
				inc_X();
				this->set_next(op);
//				cout << "CASE 25" << endl;
				
			}
			break;
		case 26:{
				dec_X();
				this->set_next(op);
//				cout << "CASE 26" << endl;
			}
			break;
		case 27:{
				push();
				this->set_next(op);
//				cout << "CASE 27" << endl;
			}
			break;
		case 28:{		
				pop(); 
				this->set_next(op);
//				cout << "CASE 28" << endl;
			}
			break;							
		case 29:{	if (interrupt == false && WAIT == false)
				{
					this->set_iFlag(0);
				}									
				if(interrupt == false && this->get_iFlag() == 0)
				{
			//		cout << "SYSTEM INTERRUPT" << endl;
					Int(op); 
					this->set_pc(1500);
				}
				else if (interrupt == true)
				{
					WAIT = true; 				
					this->set_iFlag(0); 
					this->set_stat(0);
				}
			}break;
		case 30:{
				IRet();
				if(WAIT == true && this->get_iFlag() == 1)
				{
					WAIT = false; 	
					this->set_iFlag(0);			
					this->set_ir(29);
					this->set_op(OP);
					this->set_stat(2);	
				}else if(WAIT == true && this->get_iFlag() == 0)
				{
					WAIT = false; 
					this->set_iFlag(1);			
					this->set_ir(-1);
					this->set_op(OP);
					this->set_stat(2);	
					
				}else if(WAIT == false)
				{			
					this->set_next(OP); 	
				}
			} break;
		case 50:{
				this->set_stat(3);
			}break; 
		default:{
			//	cout << "TIMER INTERRUPT " << endl; 
				Int(op);
				this->set_pc(1000);
			}		
	}
	
		
}
void CPU::save_last()
{
	LAST = this->get_stat(); 
}
int CPU::get_last()
{
	return LAST; 
}			
void CPU::Int(int op)
{
	interrupt = true; 
	sys_mode = true; 
	SP = 1999;
	FP = 1900; 
	this->save_reg(op); 
	this->reset_reg();
}
void CPU::reset_reg()
{
	AC = 0;
	X = 0;
	Y = 0;
	OP = 0;
}
void CPU::save_reg(int op)
{
	this->dec_sp();
	this->set_sp(PC);//save PC  
	this->push();//save AC
	this->dec_sp();
	this->set_sp(X);//save X
	this->dec_sp();
	this->set_sp(Y);//save Y
	this->dec_sp();
	this->set_sp(op);
	this->set_stat(0); 
	 
}
void CPU::IRet()
{
	this->restore_reg();
	sys_mode = false; 
	SP = 999; 
	FP = 900;
	interrupt = false; 
//	cout << "INTERRUPT COMPLETE" << endl; 
}
void CPU::restore_reg()
{
	OP = this->get_sp();
	this->inc_sp(); 
	Y = this->get_sp();
	this->inc_sp();
	X = this->get_sp();
	this-> inc_sp();
	AC = this->get_sp(); 
	this->inc_sp();
	PC = this->get_sp(); 
	this->inc_sp();

}
void CPU::Load_val(int op)
{
	AC = op;				
//	cout << "LOADING VALUE: " << op << " INTO AC" <<endl; 
	this->print_ac();
//	cout << "CASE 1" << endl;
	this->set_stat(0); 
	if (interrupt == false)
	{
		this->save_last();
	}
}
void CPU::Load_addr(int addr)
{
	if(interrupt == false)
	{
		IC--;
	}
	this->store_pc(); 
	this->set_pc(addr);
	this->set_next(1);
//	cout << "CASE 2" << endl;
}
void CPU::Load_ind(int addr)
{
	if(interrupt == false)
	{
		IC--;
	}
	this->store_pc(); 
	this->set_pc(addr);
	this->set_next(1); 
//	cout << "CASE 3" << endl;
}
void CPU::Load_idxX(int addr)
{
	if(interrupt == false)
	{
		IC--;
	}
	this->store_pc(); 
	int val = addr + X;
	this->set_pc(val);

	this->set_next(1); 
	//cout << "CASE 4" << endl;
}
void CPU::Load_idxY(int addr)
{
	if (interrupt == false)
	{
		IC--;
	}
	this->store_pc(); 
	int val = addr + Y;
	this->set_pc(val);
	this->set_next(1); 
	//cout << "CASE 5" << endl;
}
void CPU::Load_spX()
{
	AC = this->get_sp() + X;
	//	this->print_ac(); 
	//cout << "CASE 6" << endl;
}
void CPU::push()
{
	this->dec_sp(); //dec then set
	this->set_sp(AC); 
}
void CPU::pop()
{
	AC = this->get_sp();//get then inc 
	this->inc_sp();
//	this->print_ac();  
}
void CPU::store_pc()
{
	this->set_fp(PC);
	SFLAG = true; 
}
void CPU::restore_pc()
{	
	PC = this->get_fp();
	SFLAG = false; 
}

void CPU::ret()
{
	this->restore_pc(); 
	this->jump(PC); 
}
void CPU::call_addr(int addr)
{
	this->store_pc(); 
	this->jump(addr); 
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
	if (interrupt == false)
	{
 		this->save_last();
	}
}
void CPU::jump(int addr)
{
		this->set_pc(addr); 
//		cout << "CASE 20" << endl;
		this->set_stat(0);
		if(interrupt ==false)
		{
			this->save_last();
		}
}
void CPU::jump_if_not_equal(int addr)
{
//	cout << "CASE 22" << endl;
//	this->print_ac(); 
	if (AC != 0)
	{
		this->jump(addr); 
	}
	else
	{
		this->set_stat(0); 
		if(interrupt == false)
		{
			this->save_last();
		}
	}
}
void CPU::jump_if_equal(int addr)
{
//	this->print_ac(); 
	if (AC == 0)
	{
		this->jump(addr); 
	//	cout << "CASE 21" << endl;
	}
	else
	{
		this->set_stat(0); 
		if(interrupt == false)
		{
			this->save_last();
		}
	}
}
void CPU::copy_to_SP()
{
	this->set_sp(AC);
	
}
void CPU::copy_from_SP()
{
	AC = this->get_sp(); 
//	this->print_ac();
}
void CPU::copy_to_X()
{
	X = AC;
//	this->print_X();
}
void CPU::copy_from_X()
{
	AC = X; 
//	this->print_ac();
}
void CPU::copy_to_Y()
{
	Y = AC;
//	this->print_Y();
}
void CPU::copy_from_Y()
{
	AC = Y; 
//	this->print_ac();
}
void CPU::inc_X()
{
	X+=1;
//	this->print_X();
}
void CPU::dec_X()
{
	X-= 1;
//	this->print_X();
}
void CPU::sub_X()
{
	AC -= X; 
//	this->print_ac();
}
void CPU::sub_Y()
{
	AC -= Y;
//	this->print_ac(); 
}
void CPU::add_X()
{
	AC += X; 
//	this->print_ac(); 
}
void CPU::add_Y()
{
	AC += Y;
//	this->print_ac(); 
}
void CPU::get()
{
	AC = rand() % 100 + 1; 
//	this->print_ac(); 
}
	
