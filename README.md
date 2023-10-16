# Mini-Shell - Minimalistic and Elegant Unix-inspered Shell

![mybadge](https://badgen.net/badge/SKILLS/%20C,%20Unix,%20Shell/blue?scale=1.2)

#### The aim of this project is to create a functional Shell to better understand Unix logic.

🔧 System Requirements:
   - Operating System: Linux 64_X86 Distribution
   - Software: [gcc](https://gcc.gnu.org/), [make](https://www.gnu.org/software/make/), [gnu readline library](https://tiswww.case.edu/php/chet/readline/rltop.html)

## Usage

To run the Mini-Shell, open your terminal and run this command:

```shell
cd /path/to/project/directory
make && ./minishell
```

## Functionalities implemented

- Redirections: `<`, `>`, `<<`, `>>`/
- Pipes : `|`.
- Expansion : `$` for environment variables.
- Exit Status : `$?`.
- Simple Quotes : Prevent the shell from interpreting the meta-characters in the quoted sequence.
- Double Quotes : Prevent the shell from interpreting the meta-characters in the quoted sequence except for `$`.
- Signals : `ctrl-C`, `ctrl-D` and `ctrl-\`.
- Command History.

## Builtins Implemented

- `echo` with option `-n`.
- `cd` with only a relative or absolute path.
- `pwd` with no options.
- `export` with no options.
- `unset` with no options.
- `env` with no options or arguments.
- `exit` with no options.
