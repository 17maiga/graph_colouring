# graph_coloring
A C implementation of the graph coloring problem. 
Developed as part of a university assigment with 
[artred02](https://github.com/artred02).

## Usage
Execution of the program is done with the following command:
``` shell
color_graph <filename>
```

`<filename>` represents the path to the input file. This input file should be
formatted according to the following convention:
- The first line should start with `V:[` and end with `];`. Between these, any
  number of vertices may be declared, with no duplicates, simply by writing
  their names and separating them by commas. Names can be composed of letters,
  numbers, and punctuation characters except the following: `[`, `]`, `,`. 
  Spaces are allowed, but beware: a trailing space between the name of a vertex
  and the comma separating it from the next name will be included in the name.
- The second line should start with `E:[` and end with `];`. Between these, any
  number of edges may be declared, again with no duplicates and separated by
  commas, using the following syntax: `(start_name,end_name)`.

Here is an example of a graph definition:

``` text
V:[A,B,C];
E:[(A,B),(A,C),(B,C)];
```

The program will create a file in the same directory as the input file, with the
same name as the input file, with the `.colored` suffix appended.
