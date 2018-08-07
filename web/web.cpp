#include <emscripten/bind.h>
#include "../src/models/sudoku_field.h"
using namespace emscripten;

float lerp(float a, float b, float t)
{
    SudokuField field;
    field.print();
    return (1 - t) * a + t * b;
}

EMSCRIPTEN_BINDINGS(my_module)
{
    function("lerp", &lerp);
}