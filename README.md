# Logger Library

This logger library provides a flexible and efficient logging system for C++ applications. It supports customizable severity levels, RGB colors for console output, and group-based logging. The library is designed to be extendable and easy to integrate into any project.

## Features

- **Predefined Severity Levels**: Includes common log levels such as `INFO`, `WARN`, `ERROR`, etc.
- **Customizable Severity Colors**: Assign custom RGB colors to different severity levels.
- **Group-Based Logging**: Log messages can be grouped for better organization.
- **Compact Mode**: Toggle between compact and verbose logging.
- **ANSI Color Codes Support**: Customizable foreground and background colors.
- **Key-Value Accumulative Storage**: Manage color mappings and other configurations easily.
- **Date-Time Timestamps**: Automatically include timestamps in the log messages.

## Installation

To use the logger library, include the header file in your project:

```cpp
#include "logger.hpp"
```

And add logger.lib to additional dependencies. Ensure that your project is set up to compile with C++11 or later.

## Usage
### Basic Logging
You can log messages with different severity levels. The logger automatically prefixes the messages with the current timestamp and the severity:

```cpp
logger::stripped("INFO") << "This is an informational message.";
logger::stripped("WARN") << "This is a warning message.";
```

### Group Logging
Log messages can be grouped for better organization:

```cpp
logger::common log("INFO", "NETWORK");
log << "Network request sent to server.";
```

### Custom Colors
You can customize the colors of the severity levels using RGB values:

```cpp
std::string customColor = logger::rgb(255, 0, 0);  // Red text
logger::severityColors["ERROR"] = customColor;
logger::stripped("ERROR") << "This is a custom-colored error message.";
```

### Compact Output
Enable compact mode to reduce the amount of space in the log messages:

```cpp
logger::stripped log("INFO", true);
log << "Compact logging enabled.";
```

### Additional Utilities
Get Current Date and Time
You can get the current timestamp using the utility function getCurrentDateTime():

```cpp
std::string timestamp = logger::getCurrentDateTime();
std::cout << "Current Timestamp: " << timestamp << std::endl;
```

### RGB Color Utilities
The logger provides utility functions to set text and background colors in RGB format:

```cpp
std::string color = logger::rgb(128, 0, 128);  // Purple text
std::string bgColor = logger::rgbBg(0, 255, 0);  // Green background
```