# cuy

**cuy** is a command-line tool to perform simple text manipulations on files and directories.

File operations:

* PENDING - Show lines of file.
    ```
    cuy --file foo.c --lines 20     # Show line 20.
    cuy --file foo.c --lines 20-30  # Show lines from 20 to 30.
    cuy --file foo.c --lines 20-    # Show lines from 20 to end of file.
    cuy --file foo.c --lines -20    # Show lines from beginning of file to 20.
    ```
* PENDING - Match patterns of a given regex expression or string
* PENDING - Remove specific lines of text in a file.
* PENDING - Replace specific patterns in a file with new text.
* PENDING - Annotate sections of code to be removed later.

Directory operations:

* PENDING - Recursively search for files matching a given pattern. Show the path of the matched files.
    ```
    cuy --find-file "foo.txt" --path /path/to/search
    cuy --find-file "foo.txt"
    ```
* PENDING - Recirsively search for directories matching a given pattern. Show the path of the matched directories.
    ```
    cuy --find-dir "foo.txt" --path /path/to/search
    cuy --find-dir "foo.txt" --recursive
    ```

