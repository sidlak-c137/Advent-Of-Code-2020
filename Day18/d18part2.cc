/**
 * @file d18part2.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-17
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 18: Operation Order ---
 * As you look out the window and notice a heavily-forested continent slowly appear over the horizon, you are interrupted by the child sitting next to you. They're curious if you could help them with their math homework.
 * 
 * Unfortunately, it seems like this "math" follows different rules than you remember.
 * 
 * The homework (your puzzle input) consists of a series of expressions that consist of addition (+), multiplication (*), and parentheses ((...)). Just like normal math, parentheses indicate that the expression inside must be evaluated before it can be used by the surrounding expression. Addition still finds the sum of the numbers on both sides of the operator, and multiplication still finds the product.
 * 
 * However, the rules of operator precedence have changed. Rather than evaluating multiplication before addition, the operators have the same precedence, and are evaluated left-to-right regardless of the order in which they appear.
 * 
 * For example, the steps to evaluate the expression 1 + 2 * 3 + 4 * 5 + 6 are as follows:
 * 
 * 1 + 2 * 3 + 4 * 5 + 6
 *   3   * 3 + 4 * 5 + 6
 *       9   + 4 * 5 + 6
 *          13   * 5 + 6
 *              65   + 6
 *                  71
 * Parentheses can override this order; for example, here is what happens if parentheses are added to form 1 + (2 * 3) + (4 * (5 + 6)):
 * 
 * 1 + (2 * 3) + (4 * (5 + 6))
 * 1 +    6    + (4 * (5 + 6))
 *      7      + (4 * (5 + 6))
 *      7      + (4 *   11   )
 *      7      +     44
 *             51
 * Here are a few more examples:
 * 
 * 2 * 3 + (4 * 5) becomes 26.
 * 5 + (8 * 3 + 9 + 3 * 4 * 3) becomes 437.
 * 5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4)) becomes 12240.
 * ((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2 becomes 13632.
 * Before you can help with the homework, you need to understand it yourself. Evaluate the expression on each line of the homework; what is the sum of the resulting values?
 * 
 * --- Part Two ---
 * You manage to answer the child's questions and they finish part 1 of their homework, but get stuck when they reach the next section: advanced math.
 * 
 * Now, addition and multiplication have different precedence levels, but they're not the ones you're familiar with. Instead, addition is evaluated before multiplication.
 * 
 * For example, the steps to evaluate the expression 1 + 2 * 3 + 4 * 5 + 6 are now as follows:
 * 
 * 1 + 2 * 3 + 4 * 5 + 6
 *   3   * 3 + 4 * 5 + 6
 *   3   *   7   * 5 + 6
 *   3   *   7   *  11
 *      21       *  11
 *          231
 * Here are the other examples from above:
 * 
 * 1 + (2 * 3) + (4 * (5 + 6)) still becomes 51.
 * 2 * 3 + (4 * 5) becomes 46.
 * 5 + (8 * 3 + 9 + 3 * 4 * 3) becomes 1445.
 * 5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4)) becomes 669060.
 * ((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2 becomes 23340.
 * What do you get if you add up the results of evaluating the homework problems using these new rules?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

typedef long long int ll;

// Order of operations
ll order(char op);

// Solve operation
ll solve(char op, ll a, ll b);

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    string s;
    ll sum = 0;
    while (std::getline(input, s)) {
        stack<ll> nums;
        stack<char> ops;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == ' ') {
                // Ignore white space
                continue;
            } else if (c == '(') {
                // Add bracket to stack
                ops.push(c);
            } else if (isdigit(c)) {
                // Handle number
                ll num = 0;
                while (i < s.size() && isdigit(s[i])) {
                    num = (num * 10) + (s[i] - '0');
                    i++;
                }
                nums.push(num);
                i--;
            } else if (c == ')') {
                // Handle brackets
                while (!ops.empty() && ops.top() != '(') {
                    ll a = nums.top();
                    nums.pop();
                    ll b = nums.top();
                    nums.pop();
                    char op = ops.top();
                    ops.pop();
                    nums.push(solve(op, b, a));
                }
                // remove opening bracket
                ops.pop();
            } else {
                // Is an operation
                while (!ops.empty() && order(ops.top()) >= order(c)) {
                    ll a = nums.top();
                    nums.pop();
                    ll b = nums.top();
                    nums.pop();
                    char op = ops.top();
                    ops.pop();
                    nums.push(solve(op, b, a));
                }
                ops.push(c);
            }
        }
        // Handle remaining calculations
        while (!ops.empty()) {
            ll a = nums.top();
            nums.pop();
            ll b = nums.top();
            nums.pop();
            char op = ops.top();
            ops.pop();
            nums.push(solve(op, b, a));
        }
        sum += nums.top();
    }
    // Return sum
    cout << "Sum: " << sum << endl;
    return 0;
}

ll order(char op) {
    switch(op){
        case '+': return 2;
        case '*': return 1;
        default: return 0;
    }
}

ll solve(char op, ll a, ll b) {
    switch(op){
        case '+': return a + b;
        case '*': return a * b;
        default: return -1;
    }
}