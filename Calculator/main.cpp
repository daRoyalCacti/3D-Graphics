#include "helper.h"
#include <vector>
#include <iostream>
#include <cmath>


int main() {
	char input[] = "10+10+10+10+10+10+10+10+10"; //answer is 90
	//char input[] = "1*1+(232.1+((20.92+3)-1)*-5)/-2"; //answer is -57.75
	//char input[] = "(232.1+((20.92+3)-1)*-5)/-2"; //answer is -58.75
	//char input[] = "(((((25.2255*1515+15)+15151*56.15615)/415.165)+15*0.1515)+555.15*(152.5615/156.1)+15)"; //answer is 2701.284348606021842631156589694550640328371252685260638984
	//char input[] = "(1+2+3/5*6*5/23)+5*(25*28+(25+25)*(214+54)/6)";
	std::vector<double> nums;
	std::vector<char> operations;

	bool done = false;
	int counter = 0;
	unsigned times_here = 0;

	std::cout << "input:\t";
	for (int i = 0; i < sizeof(input)/sizeof(char); i++) {
		std::cout << input[i];
	}
	std::cout << std::endl;

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


	//bracketing multiplication and division to comply with BOMDAS/PEMDAS
	//this is done by breaking the input up into multiple cases an exectuting an algorithm on each
	//it is entirely possible to do the algorithm without uses cases, except this is an unnecessary complication

	counter = 0;	//counter here represents how many items were added before the current search position
								//this is used because inserting elements is done from the beginning of the vector and thus the current search position will have to increase along with the position items are being inserted at
								//this cannot be made simpler by adding elements based on the end of the vector because then the amount of elements added beyond the current search position will have to be kept track of
								// - this will require a very similar to the current one employed
								//since there will always be a bracket added to the left and right of the current search position, counter will be incremented by 1 everytime a bracket is added
	for (int i = 0; i < operations.size(); i++, counter++) {
		if (operations[counter] == '*' || operations[counter] == '/') {
			if (operations[counter + 1] == 'x') { //if the next operation involves a number
				if (operations[counter - 1] == 'x') {
					//the trivial case
					//x * x = (x * x)
					operations.insert(operations.begin() + counter + 2, ')');	//the position after the x
					operations.insert(operations.begin() + counter - 1, '('); //the position before the x
					counter+=1;
				} //endif 'x'

				if (operations[counter - 1] == ')') {
					//() * x = (() * x)

					//adding the trivial right bracket
					operations.insert(operations.begin() + counter + 2, ')'); //the position after the x
					int counter2 = counter - 1; //starting at what is already checked because it is decremented in the main loop

					//keep on moving left until the bracket ends
					//this is made more complicated because there could be more brackets inside the brackets under consideration
					//to get around this, the number of left and right brackets are kept track of to add a bracket in the corret position

					int net_left = 1;	//keeping track of the number of net number of left brackets
					while (net_left != 0) {		//if there is the same amount of right brackets as left brackets, then we have found the position were a bracket needs to be aded
						if (operations[--counter2] == ')') {
							net_left++;			//a set of brackets inside of the main brackets has been found
						} else if (operations[counter2] == '(') {
							net_left--;			//the inner set of brackets has ended -- or the main set has ended and thus we are done
						}
					}
					operations.insert(operations.begin() + counter2, '(');
					counter+=1;
				} //endif )


			} else if (operations[counter + 1] == '(') { //if the next operation is a bracket
				if (operations[counter - 1] == 'x') {
					//x * () = (x * ())
					operations.insert(operations.begin() + counter - 1, '(');
					counter++;
					int counter2 = counter + 1; //starting at what is already checked because it is incremented in the main loop
					int net_right = 1;	//as stated above the number net number of right brackets needs to be kept track of in order to add the bracket in the right spot
					while (net_right != 0) {
						if (operations[++counter2] == ')') {
							net_right--;
						} else if (operations[counter2] == '(') {
							net_right++;
						}
					}
					operations.insert(operations.begin() + counter2 + 1, ')');

				} //endif 'x'

				//iterate multiple times
				else if (operations[counter - 1] == ')') {
					//() * () = (() * ())

					//same alorithm as above but repeated in both directions
					//using a slight modification of this algorithm would allow for a general way to bracket

					//left bracket
					int counter2 = counter + 1;
					int net_left = 1;

					while (net_left != 0) {
						if (operations[++counter2] == ')') {
							net_left--;
						} else if (operations[counter2] == '(') {
							net_left++;
						}

					}
					operations.insert(operations.begin() + counter2 + 1, ')');

					//right bracket
					counter2 = counter - 1;
					net_left = 1;
					while (net_left != 0) {
						if (operations[--counter2] == ')') {
							net_left++;
						} else if (operations[counter2] == '(') {
							net_left--;
						}
					}

					operations.insert(operations.begin() + counter2, '(');
					counter+=1;



				} //endif )

			} //endif (

		}	//endif 'x'

	} //end loop

	double answer = evaluate_expression(nums, operations);	//runs the 'evaluate_expression' stated in helper.h with in inputs created by the previous code

	std::cout << "answer:\t" << answer << std::endl;

	return 0;
}
