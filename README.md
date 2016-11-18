# Infix - RPN Converter

## Building

`make` in the top level folder should build tests, run tests, run memory checks,
and if all tests pass, build the final executable.

## Implementation Notes

The conversion from infix to rpn does not make use of the abstract syntax tree.
I completed this conversion using a simplified shuting yard algorithm before
understanding the capability of an abstract syntax tree, and since it works,
there is little need to change it.  Had I more time, I would fix it and
make a more elegant library.

This code assumes only valid input.  Again, time is shorter than I would like,
or it would contain a good error handling solution.  If you give it weird 
input, expect weird output.
