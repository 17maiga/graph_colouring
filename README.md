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
- Graphs should be surrounded by curly braces (`{}`). Graphs should contain at
  least a list of vertex names, separated by commas. This list should be
  surrounded by square braces (`[]`).
- Names can be composed of any letter, number or punctuation sign in the ASCII
  table except the following: `{`, `}`, `[`, `]`, `,`, `:`. Whitespace 
  characters (spaces, newlines, tabs) will be ignored no matter where they 
  occur. Duplicates will be ignored.
- Graphs may also contain a list of edges. An edge is composed of the starting
  vertex's and the ending vertex's names, separated by a comma, and the whole
  surrounded by brackets (`()`); If the graph does not contain any edges, this
  list may be ommitted.
- The input file may contain any number of graphs.

Here is an example of a graph definition:

``` text
{[A:5,B,C][(A,B)(A,C)(B,C)]}
```

The following graph definition is equivalent:

``` text
{
  [ A:5, B, C ]
  [ 
    (A, B)
    (A, C)
    (B, C)
  ]
}
```

If no output options are specified, the program will create a file in the same 
directory as the input file, with the same name as the input file, with the 
`.colored` suffix appended.

If the `-o` option is specified, the program will use `FILENAME` as the output
file, if possible. It will not create any required directories.

If the `-s` option is specified, the program will create a separate file for
each graph in the input file. These will be numbered from 1 to `n`, with `n` the
number of graphs in the input file, and this number will be appended to the end
of the output file's name.

## Sources

- [Welsh-Powell algorithm](http://mrsleblancsmath.pbworks.com/w/file/fetch/46119304/vertex%20coloring%20algorithm.pdf)
- [DSatur](https://en.wikipedia.com/wiki/DSatur)
- [RLF Algorithm](https://en.wikipedia.com/wiki/Recursive_largest_first_algorithm)
