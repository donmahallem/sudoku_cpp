#include <iostream>
#include <string.h>
#include <chrono>
#include "models/sudoku_field.h"
#include "models/sudoku_tip_field.h"
#include "sudoku_solver.h"
#include "sudoku_generator.h"

using namespace std::chrono;

inline short parseInputChar(char inp)
{
    if (inp < 48 || inp > 57)
    {
        throw 21;
    }
    return inp - 48;
}
inline SudokuField *parseInput(char *inp)
{
    SudokuField *field = new SudokuField();
    for (short i = 0; i < 9 * 9; i++)
    {
        short x = i % 9;
        short y = i / 9;
        field->set(x, y, parseInputChar(inp[i]));
    }
    return field;
}

inline int benchmark()
{
    std::cout << "Starting benchmark " << std::endl;
    milliseconds start_ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch());

    SudokuField *field = new SudokuField();
    for (int i = 0; i < 1000; i++)
    {
        field->clear();
        SudokuGenerator::generate(40, field);
        std::cout << "Done with: " << i << std::endl;
    }
    milliseconds end_ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch());
    std::cout << "End benchmak" << std::endl;
    std::cout << "Took: " << (end_ms - start_ms).count() << std::endl;
    return 0;
}

int main(int argc, char *argv[])
{

    if (argc == 2)
    {
        if (strcmp("benchmark", argv[1]) == 0)
        {
            return benchmark();
        }
    }
    else if (argc == 3)
    {
        return 0;
    }
    return 1;
}