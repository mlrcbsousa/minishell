# minishell

42 school minishell project

## Resources

- [Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree)
- [Backus Naur Form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
- [Lexical Analysis](https://en.wikipedia.org/wiki/Lexical_analysis)

### Solving the CTRL^C issue

- [termios](https://velog.io/@sham/minishell%EA%B3%BC-readline)

### Solving the CTRL^D issue

- [ansi escape](https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html)

## Example Backus Naur

Good example to think of mathematical expressions `/x+-` and the numbers 0 to 9.

In **Backus Naur** it would look something like this.

```
<expression>	::=	<number> '+' <expression>
		|	<number> '-' <expression>
		| 	<number> 'x' <expression>
		|	<number> '/' <expression>

<number>	::=	0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```

For the project:
```
/**
TODO: Add redirect commands

<command line>   ::=  <command> '|' <command line>
                  |   <command>

<command>        ::=  <simple command> '<' <filename>
                  |   <simple command> '>' <filename>
		  |   <simple command> '<<' <filename>
		  |   <simple command> '>>' <filename>
                  |   <simple command>

<simple command> ::=  <cmd path> <token list>

<token list>     ::=  <token> <token list>
                  |   (EMPTY)

**/

// t_astree* command_line();     // test "command line" possibilities
// t_astree* command_line_a();   // <command> '|' <command line>
//                               // <command>

// t_astree* command();          // test "command" possibilities
// t_astree* command_a();        // <simple command> '<' <filename>
// t_astree* command_b();        // <simple command> '>' <filename>
// t_astree* command_c();        // <simple command> '<<' <filename>
// t_astree* command_d();        // <simple command> '>>' <filename>
//                               // <simple command>

//                               // test "simple command" possibilities
// t_astree* simple_command();   // <command path> <token list>

// t_astree* token_list();       // test "token list" possibilities
// t_astree* token_list_a();     // <token> <token list>
//                               // EMPTY
```

## Development Workflow

1.  The main development branch is called `main`.

    ```bash
    git checkout main
    ```

2.  Prefix your branch name with your initials.

    ```bash
    git checkout -b ms/$FEATURE/$SUB-FEATURE
    ```

3.  Write your magical code

4.  Add and commit your changes to the branch:

    ```bash
    git add . && git commit -m "$COMMIT MESSAGE"
    ```

5.  **A note on Commit messages:** Full __capitalized__ and __punctuated__ English sentences please.
    This helps tremendously with reviewing and commit history tracking.
    Be **precise** and use the __present__ tense, as if you had written the commit before you added the code.

    - Type of commit is a useful information (a `fix`, an `improvement`, a `refactoring`, a `removal`).
    - A link to the main issue/task, this can also be done more easily in the main PR post on GitHub.
    - The message should explain why this commit is done. This will also improve the history.

6.  After merging with root branch for any updates:

    ```bash
    git push origin ms/$FEATURE/$SUB-FEATURE
    ```

7. Open a PR to merge with the `main` branch on the GitHub website.


### To merge new `main` changes on your branch

1.  Checkout to `main` from your branch.

    ```bash
    git checkout main
    ```

2.  Pull newest stuff from remote.

    ```bash
    git pull origin main
    ```

3.  Checkout to your work branch.

    ```bash
    git checkout ms/feature/sub-feature
    ```

4.  Merge your local updated `main` to your work branch.

    ```bash
    git merge main
    ```

5.  Solve conflicts if any, add and merge them.

6.  Push your updated work branch.

    ```bash
    git push
    ```
