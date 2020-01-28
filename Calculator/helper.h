#pragma once
#include <cmath>
#include <iostream>
#include <vector>

inline double charToNum(char value) {
	return (double)value - (double)'0';
}

template <typename T>
inline bool isNum(T value) {
	if (value < 0) return false;
	if (value >= 10) return false;
	return true;
}

double evaluate(double one, double two, char operation) {
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
	} else if (operation == '^') {	//wont give expected behaviour
		return pow(one,two);
	} else {
		std::cerr << operation << " is not a valid operation" << std::endl;
		exit(1);
	}
}


double evaluate_expression(std::vector<double> nums, std::vector<char> ops) {
	double answer;
	for (const auto& op : ops) {
		std::cout << op;
	}
	std::printf("\n");

	//iterate through and find all bracketed expressions to be evaluated first
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
						break;
					}
				} else if (ops[i] == 'x') {
					exp_nums.push_back(nums[counter_nums++]);
				}

				exp_ops.push_back(ops[i]);
				i++;
			}

			//exp_ops.erase(exp_ops.end() - 1);
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
	answer = new_nums[0];

	for (int i = 0; i < new_ops.size(); i++) {
		answer = evaluate(answer, new_nums[i + 1], new_ops[i]);
	}

	return answer;
}
