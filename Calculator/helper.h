#pragma once
#include <cmath>
#include <iostream>
#include <vector>

inline double charToNum(char value) {
	//uses a standard algorithm to convert from char to a number
	return (double)value - (double)'0';
}

template <typename T>
inline bool isNum(T value) {
	//this is used to evaluate if the value returned by 'charToNum' did infact return a number
	//this is done by checking if the value return is between 0 and 9 inclusive
	// - 'charToNum' only takes one char at a time so it is impossible for it to correctly return a 2 digit number
	if (value < 0) return false;
	if (value >= 10) return false;
	return true;
}

double evaluate(double one, double two, char operation) {
	//performs simple operations on 2 numbers
	// - there is likely a simpler way of doing this but this is the best way I could come up with
	if (operation == '+') {
		return one + two;
	} else if (operation == '-') {
		return one - two;
	} else if (operation == '*') {
		return one * two;
	} else if (operation == '/') {
		if (two == 0) {
			std::cerr << "cannot divide by 0" << std::endl;
			exit(1);
		} else {
			return one / two;
		}
	} else {
		//this is mainly useful for debugging
		std::cerr << operation << " is not a valid operation" << std::endl;
		exit(1);
	}
}


double evaluate_expression(std::vector<double> nums, std::vector<char> ops) {
	double answer;


	//iterate through and find all bracketed expressions to be evaluated first
	//e.g. ((..) * (..(..)..)) -> (x * y)
	int net_right = 0;
	unsigned counter_nums = 0;
	std::vector<double> new_nums;
	std::vector<char> new_ops;
	for (int i = 0; i < ops.size(); i++) {
		//if insided braketed expression
		if (net_right!=0) { //backet has been found
			std::vector<double> exp_nums;
			std::vector<char> exp_ops;

			while (net_right != 0) {

				if (ops[i] == '(') {
					net_right++;
				} else if (ops[i] == ')') {
					net_right--;
					if (net_right == 0) {
						break;	//don't want the last bracket being added
					}
				} else if (ops[i] == 'x') {
					exp_nums.push_back(nums[counter_nums++]);
				}

				exp_ops.push_back(ops[i]);
				i++;
			}

			double exp_ans = evaluate_expression(exp_nums, exp_ops);
			new_nums.push_back(exp_ans);

		}
		//if outside expression
		else {
			if (ops[i] == 'x') {
				new_nums.push_back(nums[counter_nums++]);
			} else if (ops[i] == '(') {
				net_right++;
				continue;
			} else {
				new_ops.push_back(ops[i]);
			}

		} //end outside expression

	}	//end loop
	//using the answers to the bracketed expressions, evaluate the answer to the expression given
	answer = new_nums[0];	//setting this so the recursion below will work correctly

	for (int i = 0; i < new_ops.size(); i++) {
		answer = evaluate(answer, new_nums[i + 1], new_ops[i]);
	}

	return answer;
}
