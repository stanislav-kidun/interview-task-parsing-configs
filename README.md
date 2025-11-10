# interview-task-parsing-configs


Instead of writing everything in one file, I decided to create some project structure and split the code into several files. All source files can be found in ``src`` folder. Here is some explanation of this split:

* ``config_parsing_methods`` stores all functions and methods used in parsing file data. It does not store any methods for working with mapping files, opening them, etc.

* ``config_structures`` stores definitions of main structures along with methods used to work with them (such as freeing them)

* ``input_and_output`` stores functions to either write parsed configs in a file descriptor (stdout by default) or read and preprocess data provided before parsing, for example, opening files, mapping data, and so on.

* ``utils`` stores functions and structures needed by the project to work properly but not related to the project itself. For example, there you can find the implementation of a simple Stack structure, used for storing opened nodes in config.


For comfortable building project in the project root, you can find simple CMakeLists.txt for cmake building. To build the project you can use either ``make`` command in the root folder or ``build_project.sh`` shell script. After that, you can use either created ``.out`` executable or use ``run_project.sh`` shell script. For smoother use, you can use ``build_and_run_project.sh`` shell script.