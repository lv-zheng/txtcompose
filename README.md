# Text Composer

This utility enables you to write sections of text files separately and merge
them into one, with c-like inclusion syntax.

## Dependencies

* cmake build system (or you can build by hand).
* C++14 compiler.
* Boost 1.44 or higher with filesystem library.

## Usage

Build txtcompose with cmake:

```
cmake path/to/source
make
```

Usage:

```
./txtcompose <root-file>
```

## Example

Try `./txtcompose examples/poem/a.txt`

## Syntax

Lines are matched with regex `^\s*%include\s*(<(.+)>|"(.+)")\s*$`

There are two different forms:

```
%include <path/to/file>
%include "path/to/file"
```

The first form specifies a path relative to the root file, and the second form
includes a file relative to the current file.
