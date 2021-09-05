# Bison & Flex Calculator

This project is designed
within the research activities in Saratov State University, Faculty of Computer Science and Information Technologies.

## Content

* Folder `src` contains parser source code + `Makefile` to build it.

* Submodule folder `tex` contains *LaTeX* source files + built PDF-file. If you would like to get access to those files — contact the author.

* Folder `tex-public` contains built PDF-file.

* Folder `csv` contains data provided by `test.py` script.

* `test.py` script provides benchmarking for different versions of parser.

* `graph.py` script displays results.

## Build

### Targets

* `clean` — removes temporary source files.

* `build` — builds executable file.

* `run` — starts either interactive mode or
python benchmarking script.

`Makefile` variables:

### General

* `mode` — parser mode. Possible values: `interactive`, `benchmark`.
Interactive mode allows you to use *stdin* as input, while `benchmark` mode collects data.

* `version` (optional) — parser version. Possible values: `naive`, `arena`. Naive version does computing along with parsing, while arena version builts AST and then traverse it.
    > If not stated — uses arena management version.

### Benchmarking

* `right_bound` (optional) — right bound of expression length.
    >Default value — 101

* `step` (optional) — lenght of step between expression length iterations.
    > Default value — 5

* `iter` (optional) — number of iterations parser
does with a fixed expression length.
    > Default value — 1000000

### Usage examples

Running parser in interactive mode with arena memory management:

```zsh
make run mode=interactive version=arena
```

Running parser through `test.py` script in benchmarking mode with naive memory management:

```zsh
make run mode=benchmark version=naive
```

> Additional parameters for benchmarking are passed the same way.

Displaying results:

```zsh
python3 graph.py <file1> <file2> ... <fileN>
```
