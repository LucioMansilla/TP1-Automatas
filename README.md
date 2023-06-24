# TP-Automatas

This is an academic project, which consists of the implementation of a Nondeterministic Finite Automaton (AFND). As a new enhancement, a "minigrep" feature has been added, which allows you to test a regular expression against a string right from the command line.

The minigrep feature can be run using the `grep.sh` script provided. This script not only builds the project but also accepts a regular expression and a line or phrase as arguments.

The project is written in C and Python. In C, it has different tests.

# Usage

Here are some important details to keep in mind:

## Building

Dependencies:

- [CMake >= 3.10](https://cmake.org/)

- Any C Compiler (We like [GCC](https://gcc.gnu.org/))

- In some cases you may need to install [g++](https://gcc.gnu.org/)


## Important Notes:

* Executables tests are generated in the `tests/exec` directory.
* Files "AFND_TP.dot", "AFND_TP2.dot", and "AFND.dot" are used for various tests.
* Files "AFD_TP.dot", "kleene.dot", "union.dot", "concatenate.dot", "minimize.dot", and "write_afnd.dot" are generated after running `run.sh`.
* You can find both input and output files in the `C/tests` directory.
* `run.sh` will report the test status.
* A log file will be generated after running `run.sh` in the `C/tests/exec` directory. It will contain additional information about the tests, such as printouts of automata and lists.

# MiniGrep Usage:

To run this project, it's necessary to build it first. We've provided a script that does this task for you and also accepts the necessary parameters to test the 'grep' function.

```bash
./grep.sh <regex> <line>
```
Where `<regex>` is the regular expression to test and `<line>` is the line or phrase to test against the regular expression.

For example, to test the regular expression `a*` against the line `aab`, you can run the following command:

```bash
./grep.sh "a*" "aab"
```

The output of this command will be:

```bash
The line matches the provided regular expression.
```


## How to Run `run.sh`:

To execute `run.sh` and run the tests, follow these steps:
1. Open a terminal or command prompt.
2. Navigate to the `C/tests` directory using the `cd` command.
3. Run the command `./run.sh`.
4. The script will execute the tests and print the results to the terminal or command prompt. For example:
```
test_concat passed
test_afnd_to_afd passed
test_build passed
test_build_from_dot passed
test_belongs passed
test_strings_belongs passed
test_read_and_write passed
test_union passed
test_kleene passed
test_tp1 passed
test_tp2 passed
test_minimize passed
test_parser passed 
test_mini_grep passed

Tests finished!. Check exec/logs for more information
Check tests folder for the .dot files generated
```

5. After the tests complete, a log file will be generated in the `C/tests/exec` directory. This log file will contain additional information about the tests, including printouts of automata and lists.

Feel free to explore the code and run the provided tests. If you encounter any issues, please refer to the log file for more information. Enjoy!


## The executables associated with each test are listed below:

* [Test AFND to AFD:]() `./exec/test_afnd_to_afd`
* [Test Belongs:]() `./exec/test_belongs`
* [Test Build:]() `./exec/test_build`
* [Test Build from Dot:]() `./exec/test_build_from_dot`
* [Test Concat:]() `./exec/test_concat`
* [Test Kleene:]() `./exec/test_kleene`
* [Test Minimize:]() `./exec/test_minimize`
* [Test Read and Write:]() `./exec/test_read_and_write`
* [Test Strings Belongs:]() `./exec/test_strings_belongs`
* [Test TP1:]() `./exec/test_tp1`
* [Test TP2:]() `./exec/test_tp2`
* [Test Union:]() `./exec/test_union`
* [Test Parser:]() `./exec/test_parser`
* [Test Mini Grep:]() `./exec/test_mini_grep`


# PNG files(TP1):

In the `TP-AUTOMATAS/C/assets` directory, you can find the following PNG files:

- `AFD_1.png`
- `AFD_TP.png`
- `AFND_1.png`
- `AFND_TP.png`

These files were generated by running the `automata` program located in the `TP-AUTOMATAS/C/src` directory. This program reads an automaton from a `.dot` file, converts it from AFND to AFD, and writes the resulting automaton to another `.dot` file. You can run this program by passing it two arguments: the input `.dot` file and the output `.dot` file. As an example, two input files are provided: `AFND.dot` and `AFND_TP.dot`. You can run the program as follows:

```
cd C/src
./automata <input_file> <output_file>
```


## To compile in C:

```
cd C
cmake -E make_directory build && cmake -E chdir build cmake .. && cmake --build build
```

## or:

```
cd C
mkdir build
cd build
cmake ..
make
```

## For Python(Run):

```
cd Python
python3 report.py
```

# Note:

- Make sure to have Graphviz installed on your system before attempting to view the .dot files. If you don't have it installed, you can download it from the official website: https://www.graphviz.org/download/.

- You can verify if dot is available by running the following command: dot -V.

# To view .dot files:

- Open a terminal and navigate to the directory where the .dot file is located.
  (tests/) for example \
- Run the following command to generate an image file from the .dot file: dot -Tpng <filename>.dot -o <image_filename>.png
- The image file will be generated in the same directory where the .dot file is located.

