/***************************************************************
CSCI 241         Assignment 9      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 04/01/2021
***************************************************************/

#include <iostream>
#include <iomanip>

#include "sml.h"
#include "simplesim.h"

using namespace std;
using std::setw;
using std::setfill;


/**********************************************
Function that assigns memory[i] with 7777

Does not pass any arguments

**********************************************/
simplesim::simplesim() {
	for (int i = 0; i < 100; i++)			// Loop that goes over memory 100 times and assgins 7777
		memory[i] = 7777;
}


/**********************************************
Function that loads the program

Does not pass any arguments
Returns true

**********************************************/

bool simplesim::load_program() {
	int count = 0;
	int instruction;

	while (cin >> instruction) {

		if (count > 100) {											// checks to see if count is over 100
			cout <<"*** ABEND: pgm load: pgm too large ***\n ";
			return false;
			// print error and return false.
		}

		else if(instruction == -99999)
		{
			//memory[count] = 7777;
			count++;
			return true;
			
		}

		else if (not_valid_word(instruction) && instruction != -99999) {							// Checks to see if input is a valid word
			cout << "*** ABEND: pgm load: invalid word ***\n";
			return false;
		}

		

		memory[count] = instruction;								// copys instruction to memory
		++count;													// increment count

	}

	return true;
}

/**********************************************
Function that checks if the input is not a valid word

Does not pass any arguments

**********************************************/

bool simplesim::not_valid_word(int word) const {
	return (word <= -9999 || word >= 9999);							// not a valid word if less than -9999 or over 9999
}

/**********************************************
Function that executes the program 

Does not pass any arguments

**********************************************/

void simplesim::execute_program() {
	bool done = false;
	instruction_counter = 0;

	while (!done) {												// while not done will loop
		int value = 0;

		// instruction fetch
		if(instruction_counter < 100) {							// checks instruction counter is less thsn 100
			instruction_register = memory[instruction_counter];				// assigns memory to instruction_register

			operation_code = instruction_register / 100;			//assigns instruction_register to operation code
			operand = instruction_register % 100;					// assigns instruction register to operand
		} else {
			cout << "*** ABEND: addressability error ***\n";		// error message
			return;
		}

		// instruction execute

		switch (operation_code) {									// switch statement
			case READ:
                cin >> value;										// gets value 
				if (not_valid_word(value)) {
					cout << "*** ABEND: illegal input ***\n";		// error and exit
					return;
                }

				memory[operand] = value;							// assigns value to memory
				cout << internal << setfill('0') << showpos << "READ: " 		// prints message
                     << setw(5) << memory[operand] << endl;
				break;

			case WRITE:
				cout << internal << setfill('0') << showpos << setw(5) 			//prints message
                     << memory[operand] << endl;
				break;

			case LOAD:
				accumulator = memory[operand];						// assigns memory to accumlator
				break;

			case STORE:
				memory[operand] = accumulator;						// assigns accumlator to memory
				break;

			case ADD:
				value = accumulator + memory[operand];				// assigns accumlator plus memory to value

				if(value <-9999) {									// value less than -9999
					cout << "*** ABEND: underflow ***\n";
					return;
				} else if(value > 9999) {							// value more than 9999
					cout << "*** ABEND: overflow ***\n";
					return;
				}

				accumulator = value;								// assigns value to accumlator
				break;

			case SUBTRACT:											// assigns accumlator minus memory to value
				value = accumulator - memory[operand];

				if (value <-9999) {									// value less than -9999
					cout << "*** ABEND: underflow ***\n";
					return;
				} else if(value > 9999) {							// value more than 9999
					cout << "*** ABEND: overflow ***\n";
					return;
				}

				accumulator = value;								// assigns value to accumlator
				break;

			case MULTIPLY:
				value = accumulator * memory[operand];				// assigns accumlator times memory to value

				if (value <-9999) {									// value less than -9999
					cout << "*** ABEND: underflow ***\n";
					return;
				} else if(value > 9999) {							// value more than 9999
					cout << "*** ABEND: overflow ***\n";
					return;
				}

				accumulator = value;								// assigns value to accumlator
				break;

			case DIVIDE:
				if (memory[operand] == 0) {
					cout << "*** ABEND: attempted division by 0 ***\n";
					return;
				}

				accumulator = accumulator / memory[operand];		// assigns accumlator divided by memory to value
				break;

			case BRANCH:											// first branch
				instruction_counter = operand;
				break;

			case BRANCHNEG:											// second branch
				if (accumulator < 0) {
					instruction_counter = operand;
				} else {
					instruction_counter++;
				}
				break;

			case BRANCHZERO:										// third branch
				if (accumulator == 0) {
					instruction_counter = operand;
				} else {
					instruction_counter++;
				}
				break;


			case HALT:												// Halt once its done
				cout << "*** Simplesim execution terminated ***\n";
				done = true;
				break;

			default:												// default case
				cout << "*** ABEND: invalid opcode ***\n";
				return;
		}

		if ( (operation_code != BRANCH && operation_code != BRANCHNEG &&  operation_code != BRANCHZERO) && !done)
			instruction_counter++;			
	}
}

/**********************************************
Function that prints most the input

Does not pass any arguments

**********************************************/

void simplesim::dump() const {
	// Print the registers.
	cout << endl << "REGISTERS:\n";

	cout << left << setw(24) << setfill(' ') << "accumulator: " 
         << setw(5) << internal << setfill('0') << showpos << accumulator 
         << endl;
	cout << left << setw(24) << setfill(' ') << "instruction_counter: " 
         << setw(2) << right << setfill('0') << noshowpos 
         << instruction_counter << endl;
	cout << left << setw(24) << setfill(' ') << "instruction_register: " 
         << setw(5) << internal << setfill('0') << showpos  
         << instruction_register << endl;
	cout << left << setw(24) << setfill(' ') << "operation_code: " 
         << setw(2) << right << setfill('0') << noshowpos << operation_code
         << endl;
	cout << left << setw(24) << setfill(' ') << "operand: " << setw(2)
         << right << setfill('0') << noshowpos << operand << endl;

	// Print memory.
	cout << "\nMEMORY:\n";
	cout<<"       ";

	for (int i = 0; i < 10; ++i) {
		cout << setw(6) << left << setfill(' ') << noshowpos << i;
	}
	cout << endl;

	for (int j = 0; j < 100; j++) {

        // Print location counter value if at start of line.
        if (j % 10 == 0)
        {
            cout << noshowpos << setfill(' ')
                 << right << setw(2) << j;
        }

		// Print a word.
        cout << ' ' << internal << showpos << setfill('0') 
             << setw(5) << memory[j];

		// If ten words have been printed, go to a new line.
        if ((j + 1) % 10 == 0)
            cout << endl;
	}
}

