# graph-calculator
In a Linux environment use make to get the executable.
The executable ./gcalc is provided, run it after which you will be presented with a command line.
Further details about the design of the project are provided in the design.pdf file.

1) Directed graphs are defined by set literals in the form:  { <vertex1>, <vertex2>, <vertex3> |  (<vertex1>,<vertex3>),  (<vertex3>, <vertex1>) }
2) To assign a graph to a variable you can enter: "g1 = <graph literal>" or "g1 = g2".
3) To print a graph use: "print(g1)" or "print(<graph literal>)".
4) Available operations include: union (+), intersection (^), power (*) and brakets to ensure order of operations.
5) A possible command would be (assuming all variables are initialized): g5 = (g1 ^ g2) + (<graph literal> * g4)
6) Enjoy :) .
