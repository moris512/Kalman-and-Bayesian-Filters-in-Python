/* cheatsheet.cpp
A comprehensive C++ cheat sheet covering basic syntax, control structures,
functions (including lambdas), STL containers, classes, file I/O, error handling, and more.
This example is written for modern C++ (C++20 features are demonstrated where applicable).
*/

#include <iostream>    // Standard I/O streams
#include <fstream>     // Standard File I/O streams 
#include <vector>      // For std::vector
#include <string>      // For std::string
#include <map>         // For std::map
#include <set>         // For std::set
#include <tuple>       // For std::tuple and structured bindings (C++17)
#include <stdexcept>   // For exceptions (Error handling)
#include <algorithm>   // For standard algorithms
#include <ranges>      // For C++20 ranges (optional)
/*Remember that: 
Auto-Type Deduction is from C++11 onwards (e.g., auto x = 42).
Ranged-Based Loops are from C++11 onwards.
Lambda Functions are from C++11 onwards.
*/

/*FAQ

0. Types

Note:
Ordered means that it keeps the order the item was inserted.
Indexed means I can access the item by its index (place) in the container.

# Array: Fixed size, Ordered, Indexed.
array<int, 3> a = {1, 2, 3};

# Vector: Dynamic size, Ordered, Indexed.
vector<int> v = {1, 2, 3};

# List: Dynaic size, Ordered, Not Indexed.
list<int> l = {1, 2, 3}

# Map: Dynamic size, Ordered, Not Indexed (but access by key).
map<string, int> ages;
ages["Alice"]=30;

# Unordered Map (Hash): Dynamic size, Unordered, Not Indexed (like python dict)
unordered_map<string, int> ages;
ages["Alice"]=30;

# Tuple: Fixed size, Ordered, Indexed (stored a fixed group of different types)
Note that a Pair is a Tuple but of size 2 (std::tuple<T1,T2>)
tuple<int, string, double> myData = {25, "Alice", 3.14};

So I can extract data like:
int age = std::get<0>(myData);
string name = std::get<1>(myData);

Or equivalently (and automatically) from C++17:
auto [age, name] = myData;

1. Why does main return 0?

Since main was declared as int main(), the function returns and interger.
Returning 0 is the convention for "successful execution".
If it doesn't return 0 it means there's something wrong with the code.

2. Caution with ' ' vs " "

' ' are used for single characters: char c = 'A';
" " are used for strings: string s = "Hello";

3. Ranged Based Loops

Used to iterated over containers like vectors, arrays, tuples, etc.
E.g., 
vector<int> nums = {1, 2, 3, 4};

# Priting the elements of the vector
for (int x : nums){
    cout << x << " ";
}

# Modifying the elements of the vector
# int &x is a reference to each element.
# if I had used x instead, it would only modify a copy but nums would have stayed the same.
for (int &x : nums){
    x *= 2; # multiplies each element by 2 --> {2, 4, 6, 8}.
}

4. Lambda Functions (Anonymous inline functions)

# Without Variable Capture
auto f = [](int a, int b) -> int {return a+b; };
cout << f(3,4); # Prints 7

# With Variable Capture (i.e., a copy of x and thus, not changing x)
int x = 5;
auto f = [x](int y) { return x + y; };

# Capture by Reference
int x = 10;
auto f = [&x](int y) { return x += y; };
f(5); # Modifies the value of x to 15
f(2); # Modifies the value of x to 17

5. Maps
Stores <key, value> pairs (ordered by key), and uses binary search tree internally.
An unordered_map uses hash tables for access (faster) -- Equivalent to Python dict.

map<string, int> age;

age["Alice"] = 30;
age["Bob"] = 25;

cout << age["Bob"]; # Outputs 25

6. Sets
Stores unique elements in stored order.
Duplicates are automatically removed
An unordered_set provides faster unordered access.

set<int> nums = {4, 1, 3, 2, 2};

for (int n : nums){
    cout << n << " "; # Prints 1, 2, 3, 4
}

7. Concepts
Rules for templates, e.g., "This function should only accept certain types"
#include <concepts>

template<typename T>
concept Number = std::is_arithmetic_v<T>;

template<Number T>
T square(T x){
    return x*x;
}

8. Ranges
A better way to filter and transform containers (lists, arrays, etc.)
#include <ranges>
#include <vector>
#include <iostream>
using namespace std;
namespace rv = std::ranges::views;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};

    # Only keep even numbers and square them
    auto result = nums 
                  | rv::filter([](int x) { return x % 2 == 0; }) 
                  | rv::transform([](int x) { return x * x; });

    for (int x : result)
        cout << x << " ";  // Output: 4 16
}



9. Error Handling (Exceptions)

try{
    if (divisor == 0)
        throw runtime_error("Division by zero");
    int result = a/divisor;
} catch (const exception& e){
    cerr << "Error: " << e.what() << endl;
}

*/

using namespace std;

//-------------------------------------------------------------
// Inline function: adds two integers.
inline int add(int a, int b) {
    return a + b;
}

//-------------------------------------------------------------
// A simple class demonstrating object-oriented programming.
class Person {
public:
    // Constructor
    Person(const string &name, int age) : name(name), age(age) { }
    
    // Member function to introduce the person.
    void introduce() const {
        cout << "Hi, I'm " << name << " and I'm " << age << " years old." << endl;
    }
    
private:
    string name;
    int age;
};

//-------------------------------------------------------------
// Main function: Entry point of the program.
int main() {
    // --- Basic I/O and Variables ---
    cout << "C++ Cheat Sheet Program" << endl;

    int a = 5;
    double pi = 3.14159;
    char letter = 'A';
    bool flag = true;
    string greeting = "Hello, World!";
    
    cout << "Integer a: " << a << endl;
    cout << "Double pi: " << pi << endl;
    cout << "Character: " << letter << endl;
    cout << "Boolean flag: " << boolalpha << flag << endl;
    cout << "String: " << greeting << endl;
    
    // --- Auto Type Deduction ---
    auto x = 42;           // x is deduced as int
    auto y = 3.14;         // y is deduced as double
    cout << "Auto variables: x = " << x << ", y = " << y << endl;
    
    // --- Control Structures ---
    // If-Else Statement
    if (a > 10) {
        cout << "a is greater than 10" << endl;
    } else if (a == 10) {
        cout << "a equals 10" << endl;
    } else {
        cout << "a is less than 10" << endl;
    }
    
    // Switch Statement
    int value = 2;
    switch (value) {
        case 1:
            cout << "Value is One" << endl;
            break;
        case 2:
            cout << "Value is Two" << endl;
            break;
        default:
            cout << "Value is Other" << endl;
            break;
    }
    
    // For Loop (traditional)
    cout << "For loop (0 to 4): ";
    for (int i = 0; i < 5; ++i) {
        cout << i << " ";
    }
    cout << endl;
    
    // Range-based For Loop (C++11 onward)
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << "Range-based loop over vector: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    
    // While Loop
    int count = 0;
    cout << "While loop (0 to 4): ";
    while (count < 5) {
        cout << count << " ";
        ++count;
    }
    cout << endl;
    
    // --- Functions and Lambdas ---
    // Calling a regular function
    cout << "Sum using add(): " << add(3, 4) << endl;
    
    // Lambda Function for multiplication (C++11 onward)
    auto multiply = [](int a, int b) -> int {
        return a * b;
    };
    cout << "Product using lambda: " << multiply(3, 4) << endl;
    
    // --- Using Tuple and Structured Bindings (C++17) ---
    tuple<int, string> myTuple = {42, "Answer"};
    auto [num, text] = myTuple; // structured binding: extracts tuple elements
    cout << "Tuple contains: " << num << " and " << text << endl;
    
    // --- Standard Library Containers ---
    vector<string> fruits = {"apple", "banana", "cherry"};
    map<string, int> fruitPrices = {{"apple", 3}, {"banana", 2}, {"cherry", 5}};
    set<int> uniqueNumbers = {1, 2, 3, 2, 1}; // duplicates automatically removed
    
    cout << "Fruits: ";
    for (const auto &fruit : fruits) {
        cout << fruit << " ";
    }
    cout << endl;
    
    // Using C++20 ranges to transform a container (optional, if supported)
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << "Squares of numbers: ";
    for (int n : numbers | views::transform([](int n) { return n * n; })) {
        cout << n << " ";
    }
    cout << endl;
    
    // --- File I/O ---
    // Write to a file
    {
        ofstream outfile("output.txt");
        outfile << "This is a line written to the file." << endl;
        outfile.close();
    }
    // Read from the file
    {
        ifstream infile("output.txt");
        string line;
        cout << "File output.txt contents:" << endl;
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    }
    
    // --- Error Handling ---
    try {
        // Intentional error: division by zero
        int dividend = 10;
        int divisor = 0;
        if (divisor == 0) {
            throw runtime_error("Division by zero error!");
        }
        cout << dividend / divisor << endl;
    } catch (const exception &e) {
        cerr << "Caught an exception: " << e.what() << endl;
    }
    
    // --- Object-Oriented Programming ---
    Person bob("Bob", 25);
    bob.introduce();
    
    // End of program
    cout << "\nProgram finished. Press Enter to exit...";
    cin.get();  // Wait for user to press Enter
    return 0;
}
