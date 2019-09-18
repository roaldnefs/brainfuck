#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

static void show_usage(string name)
{
    cerr << "usage: " << name << " <path>\n\n"
         << "options:\n"
         << "  -h --help\tshow this help message"
         << endl;
}

int interpret(string path)
{
    vector<char> buffer;               // holds the program

    ifstream infile(path, ios::in);
    if (infile.is_open()) {
        char character;
        while (infile.get(character))         // read the brainfuck program character
        {                                  // by character
            switch (character)             // only add brainfuck characters to the
            {                              // program buffer
                case '>':
                    [[fallthrough]];
                case '<':
                    [[fallthrough]];
                case '+':
                    [[fallthrough]];
                case '-':
                    [[fallthrough]];
                case '.':
                    [[fallthrough]];
                case ',':
                    [[fallthrough]];
                case '[':
                    [[fallthrough]];
                case ']':
                    buffer.push_back(character);
                    break;
            }
        }
        infile.close();
    }
    else {
      cerr << "Unable to open file" << endl;
      return 1;
    }

    vector<char> memory (3000);        // holds the memory
    char *ptr = memory.data();         // holds the pointer to the memory

                                       // loop over the program
    for (size_t idx = 0; idx < buffer.size(); ++idx)
    {
        switch (buffer.at(idx))        // current character at index in vector
        {
            case '>':                  // move the pointer to the right
                ++ptr;
                break;

            case '<':                  // move the pointer to the left
                --ptr;
                break;

                                       // increment the memory cell under the
            case '+':                  // pointer
                ++*ptr;
                break;

                                       // decrement the memory cell under the
            case '-':                  // pointer
                --*ptr;
                break;

                                       // output the character signified by the
            case '.':                  // cell at the pointer
                cout.put(*ptr);
                break;

                                       // input a character and store it in the
            case ',':                  // cell at the pointer
                cin.get(*ptr);
                break;
                                       // jump past the matching ']' if the cell
            case '[':                  // under the pointer is '0'
                if (*ptr == 0)
                {
                    for (size_t peek_idx = (idx + 1), skip = 0; peek_idx < buffer.size(); ++peek_idx)
                    {
                        switch (buffer.at(peek_idx))
                        {
                            case '[':
                                ++skip;
                                break;

                            case ']':
                                if (skip == 0)
                                {
                                    idx = peek_idx;
                                    peek_idx = buffer.size();
                                }
                                else
                                    --skip;
                                break;
                        }
                    }
                }
                break;

                                       // jump back to the matching '[' if the
            case ']':                  // cell under the pointer is nonzero
                if (*ptr != 0)
                {
                    for (size_t peek_idx = (idx - 1), skip = 0; peek_idx > 0; peek_idx--)
                    {
                        switch (buffer.at(peek_idx))
                        {
                            case ']':
                                ++skip;
                                break;

                            case '[':
                                if (skip == 0)
                                {
                                    idx = peek_idx;
                                    peek_idx = buffer.size();
                                }
                                else
                                    --skip;
                                break;
                        }
                    }
                }
                break;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        show_usage(argv[0]);
        return 1;
    }

    string argument = argv[1];         // holds the second argument
                                       // display usage on help flags
    if (argument == "-h" || argument == "--help")
    {
        show_usage(argv[0]);
        return 0;
    }


    return interpret(argument);        // interpret the brainfuck program
}
