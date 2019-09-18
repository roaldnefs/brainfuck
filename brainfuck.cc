#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<char> memory (3000);        // holds the memory
    vector<char> buffer;               // holds the program
    char *ptr = memory.data();         // holds the pointer to the memory

    char c;                            // holds a single character
    while(cin.get(c))                  // read the brainfuck program character
        buffer.push_back(c);           // by character

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
                // TODO
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
}
