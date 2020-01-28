#include "helper.h"
#include <vector>
#include <iostream>
#include <cmath>


int main() {
	char input[] = "1*1+(232.1+((20.92+3)-1)*-5)/-2"; //answer is -57.75
	//char input[] = "(232.1+((20.92+3)-1)*-5)/-2"; //answer is -58.75
	//char input[] = "(((((25.2255*1515+15)+15151*56.15615)/415.165)+15*0.1515)+555.15*(152.5615/156.1)+15)"; //answer is 2701.284348606021842631156589694550640328371252685260638984
	//char input[] = "(1+2+3/5*6*5/23)+5*(25*28+(25+25)*(214+54)/6)";
	std::vector<double> nums;
	std::vector<char> operations;

	bool done = false;
	int counter = 0;
	unsigned times_here = 0;


	for (int i = 0; i < sizeof(input)/sizeof(char) - 1; i++) {
		if (isNum(charToNum(input[i]))) {
			double new_num = charToNum(input[i]); //a digit of a number in a given equation

			//if the number is negative
			//that is to say that there is a negative sign infront of it which is not a minus sign
			// - this is found by checking that there is a '-' sign infront of it but there is a symbol before the '-' sign (e.g. '*')
			if (input[i - 1] == '-' && !isNum(charToNum(input[i - 2])) && input[i - 2] != ')') {
				new_num *= -1; 	//easiest way to make the number negative
			}

			//the making of integers
			while (!done) {	//keep repeating until the next digit isnt a number
				i++;	//once a digit is determined to be part of a number, no need to check it again
				if (isNum(charToNum(input[i]))) {
					new_num *= 10;												//times the previous number by 10 so the last digit is 0, allowing for the new digit to be added
					new_num += charToNum(input[i]);	//to make an integer

				} else {
					done = true;	//the number is finished
				}
			}
			done = false;

			//the adding of decimals
			if (input[i] == '.') {	//if the digit is a decimal -- this will generally come after an integer
				while (!done) {				//keep repeating until the next digit isn't a number
					i++;						//check next digit
					if (isNum(charToNum(input[i]))) {
						times_here++;		//used to determin how many digits of the number of decimals
						new_num *= 10;				//essientally making the a bigger integer
						new_num += charToNum(input[i]);		//this method is saving on the number of 'pow' calls required
																							//the other method is new_num += charToNum(input[i]) * pow(10, -times_here)
																							// - this method however wont force the numbers to get really big (possible consideration)
					} else {
						done = true;
					}
				}
				new_num /= (double)pow(10, times_here); 	//turning what was a large number to the actual number
																									//not sure if more efficient to times by the negative power?

			}

			//variable resetting
			times_here = 0;
			done = false;


 			i--;	//because it is then incremented in the loop
			nums.push_back(new_num);		//filling the array of numbers with the numbers found
			operations.push_back('x');	//operations requires x for convenience of computation
		} else {
			if (input[i] != '-' || isNum(charToNum(input[i - 1])) || input[i - 1] == ')') {	//dont include negative signs
				operations.push_back(input[i]);
			}

		}
	}




	for (const auto& num : nums) {
		std::cout << num << std::endl;
	}
	std::printf("\n");

	for (const auto& operation : operations) {
		std::cout << operation;
	}
	std::printf("\n\n");


	//need to add check if if something is already bracketed
	std::vector<char> f_operations(operations.begin(), operations.end());
	counter = 0;
	for (int i = 0; i < f_operations.size(); i++) {
		//std::cout << i << std::endl;
		if (f_operations[counter] == '*' || f_operations[counter] == '/') {
			if (f_operations[counter + 1] == 'x') { //if the next operation involves a number
				if (f_operations[counter - 1] == 'x') {
					//x * x = (x * x)
					f_operations.insert(f_operations.begin() + counter + 2, ')');	//the position after the x
					f_operations.insert(f_operations.begin() + counter - 1, '('); //the position before the x
					counter+=1;
				} //endif 'x'

				if (f_operations[counter - 1] == ')') {
					//() * x = (() * x)
					f_operations.insert(f_operations.begin() + counter + 2, ')'); //the position after the x
					int counter2 = counter - 1; //starting at what is already checked because it is decremented in the main loop
					int net_left = 1;
					while (net_left != 0) {
						if (f_operations[--counter2] == ')') {
							net_left++;
						} else if (f_operations[counter2] == '(') {
							net_left--;
						}
					}
					f_operations.insert(f_operations.begin() + counter2, '(');
					counter+=1;
				} //endif )


			} else if (f_operations[counter + 1] == '(') { //if the next operation is a bracket
				if (f_operations[counter - 1] == 'x') {
					//x * () = (x * ())
					f_operations.insert(f_operations.begin() + counter - 1, '(');
					counter++;
					int counter2 = counter + 1; //starting at what is already checked because it is incremented in the main loop
					int net_left = 1;
					std::printf("\n");
					while (net_left != 0) {
						if (f_operations[++counter2] == ')') {
							net_left--;
						} else if (f_operations[counter2] == '(') {
							net_left++;
						}
					}
					f_operations.insert(f_operations.begin() + counter2 + 1, ')');

				} //endif 'x'

				//iterate multiple times
				else if (f_operations[counter - 1] == ')') {
					//() * () = (() * ())
					//left bracket
					int counter2 = counter + 1;
					int net_left = 1;
					std::printf("\n");
					while (net_left != 0) {
						if (f_operations[++counter2] == ')') {
							net_left--;
						} else if (f_operations[counter2] == '(') {
							net_left++;
						}

					}
					f_operations.insert(f_operations.begin() + counter2 + 1, ')');

					//right bracket
					counter2 = counter - 1;
					net_left = 1;
					while (net_left != 0) {
						if (f_operations[--counter2] == ')') {
							net_left++;
						} else if (f_operations[counter2] == '(') {
							net_left--;
						}
					}

					f_operations.insert(f_operations.begin() + counter2, '(');
					counter+=1;



				} //endif )

			} //endif (

		}	//endif 'x'
		counter++;
	} //end loop


	for (const auto& operation : f_operations) {
		std::cout << operation;
	}
	std::printf("\n");

	double answer = evaluate_expression(nums, f_operations);

	std::cout << "answer: " << answer << std::endl;

	return 0;
}
