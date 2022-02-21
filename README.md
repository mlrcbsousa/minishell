# minishell

42 school minishell project

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
