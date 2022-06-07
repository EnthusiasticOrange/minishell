# Minishell

## Description
The objective of this project is to create a simple shell. It helps to learn a lot about processes and file descriptors.

For more detais about this project refer to [**`the subject`**](en.subject.pdf).

## Prerequisites
THe project is using `MiniLibX` library. It is a tiny graphics library and can be used only on macOS. Library source files are located in [`srcs/mlx`](srcs/mlx) directory of this repository.

## Compilation
The project uses the `gcc` compiler in `Makefile`. The resulting binary is called `minishell`.

```shell
$ make
```

## Usage
To start the project just run compiled binary from the root of the repository:
```shell
$ ./minishell
```
 This simple shell can be run only in interactive mode. All program arguments will be ignored.