# Simple logger C++

Writes completely different information to various sources. Instruction:
Please, include your project this file:
```logger\logger\core\log.h```
First, initialize the logger using the log_init method, and pass the application name, its version (you can also send empty lines) and initialization parameters (platform specific) into it. 

Next, call one of four methods, depending on the logging:
- log_debug - message;
- log_error - error;
- log_critical_error - critical error with application termination;
- log_warning is a warning.

And pass any number of arguments to the function. Arguments are separated by whitespace, and for everyone argument operator<< (ostream) must be overloaded for output. Each method returns false if the logger is not initialized, or true if the logger is ready to work. Automatic stack trace output is supported for everyone OS.

Using libraries:

| Library | Link |
| ------ | ------ |
| chtml | [HTML parser for C++][chtml_link] |


   [chtml_link]: <https://github.com/tinfoilboy/CTML>
