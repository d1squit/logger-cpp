#pragma once

#include <ctime>
#include <initializer_list>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

#define WIN32_LEAN_AND_MEAN

namespace logger {
	constexpr auto RESET = "\033[0m";

	constexpr auto BLACK = "\033[30m";
	constexpr auto RED = "\033[31m";
	constexpr auto GREEN = "\033[32m";
	constexpr auto YELLOW = "\033[33m";
	constexpr auto BLUE = "\033[34m";
	constexpr auto MAGENTA = "\033[35m";
	constexpr auto CYAN = "\033[36m";
	constexpr auto WHITE = "\033[37m";
	constexpr auto RGB = "\033[38;2;";

	constexpr auto BG_BLACK = "\033[40m";
	constexpr auto BG_RED = "\033[41m";
	constexpr auto BG_GREEN = "\033[42m";
	constexpr auto BG_YELLOW = "\033[43m";
	constexpr auto BG_BLUE = "\033[44m";
	constexpr auto BG_MAGENTA = "\033[45m";
	constexpr auto BG_CYAN = "\033[46m";
	constexpr auto BG_WHITE = "\033[47m";
	constexpr auto BG_RGB = "\033[48;2;";

	/// Get current datetime in [YYYY-MM-DD hh:mm:ss] format
	std::string getCurrentDateTime();

	/// Get ANSI escape sequence for RGB text color
	std::string rgb(int r, int g, int b);

	/// Get ANSI escape sequence for RGB background color
	std::string rgbBg(int r, int g, int b);

	/// A template class to manage accumulative key-value storage
	template<typename T, typename U>
	class accumulative {
	private:
		std::map<T, U> map;
	public:
		accumulative() = default;
		accumulative(std::initializer_list<std::pair<const T, U>> init_list);

		size_t count(const T& key) const;
		U& operator[](const T& key);
	};

	/// Predefined color mappings for severity levels
	extern accumulative<std::string, std::string> severityColors;

	/// Predefined color mappings for groups
	extern accumulative<std::string, std::string> groupColors;

	/// Base class for logging messages
	class common {
	protected:
		bool compact; ///< Flag to determine if the output should be filled with spaces
	public:
		/// Constructor with optional compact mode
		/// @param compact Whether to use compact output (default: false)
		explicit common(bool compact = false);

		/// Constructor with severity and group settings
		/// @param severity Log severity level
		/// @param group Log group name
		/// @param compact Whether to use compact output (default: false)
		/// @param recursive Whether to print internal logger warnings (default: true)
		common(const std::string& severity, const std::string& group, bool compact = false, bool recursive = true);

		/// Output stream operator for logging
		template<class T>
		logger::common& operator<<(T part);

		/// Destructor that ends the log line
		~common();
	};

	/// Derived class for stripped logging (no group information)
	class stripped : public common {
	public:
		/// Constructor for stripped logging
		/// @param severity Log severity level (e.g., "INFO", "WARN")
		/// @param compact Whether to use compact output (default: false)
		/// @param recursive Whether to print internal logger warnings (default: true)
		explicit stripped(const std::string& severity, bool compact = false, bool recursive = true);
	};
}
