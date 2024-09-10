#include "pch.h"
#include "logger.h"
#include <corecrt.h>
#include <ctime>
#include <initializer_list>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace logger {
	std::string getCurrentDateTime() {
		std::time_t now = std::time(nullptr);
		std::tm localTime{};

#ifdef _MSC_VER
		localtime_s(&localTime, &now);
#else
		localTime = *std::localtime(&now);
#endif
		std::ostringstream oss;
		oss << "[" << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "]";
		return oss.str();
	}

	std::string rgb(int r, int g, int b) {
		return RGB + std::to_string(r) + ';' + std::to_string(g) + ';' + std::to_string(b) + 'm';
	}

	std::string rgbBg(int r, int g, int b) {
		return BG_RGB + std::to_string(r) + ';' + std::to_string(g) + ';' + std::to_string(b) + 'm';
	}

	template<typename T, typename U>
	accumulative<T, U>::accumulative(std::initializer_list<std::pair<const T, U>> init_list) : map(init_list) {}

	template<typename T, typename U>
	size_t accumulative<T, U>::count(const T& key) const {
		return map.count(key);
	}

	template<typename T, typename U>
	U& accumulative<T, U>::operator[](const T& key) {
		return map[key];
	}

	accumulative<std::string, std::string> severityColors = {
		{"INFO", GREEN},
		{"WARN", YELLOW},
		{"ERROR", RED},
		{"FATAL", BG_RED},
	};

	accumulative<std::string, std::string> groupColors = {
		{"LOGGER", rgbBg(70, 70, 70)},
	};

	common::common(bool compact) : compact(compact) {}

	common::common(const std::string& severity, const std::string& group, bool compact, bool recursive) : compact(compact) {
		std::string severityColor, groupColor;

		if (severityColors.count(severity)) severityColor = severityColors[severity];
		else if (recursive) common("WARN", "LOGGER", true, false) << "Severity category '" << severity << "' used in following message does not exist";

		if (groupColors.count(group)) groupColor = groupColors[group];
		else if (recursive) common("WARN", "LOGGER", true, false) << "Group '" << group << "' used in following message does not exist";

		std::cout << getCurrentDateTime() << ' ' << severityColor << severity << RESET << ' ' << groupColor << group << RESET << ' ';
	}

	template<class T>
	common& common::operator<<(T part) {
		std::cout << part << (compact ? "" : " ");
		return *this;
	}

	common::~common() {
		std::cout << '\n';
	}

	stripped::stripped(const std::string& severity, bool compact, bool recursive) : common(compact) {
		std::string severityColor;

		if (severityColors.count(severity)) severityColor = severityColors[severity];
		else if (recursive) common("WARN", "LOGGER", true) << "Severity category '" << severity << "' used in following message does not exist";

		std::cout << getCurrentDateTime() << ' ' << severityColor << severity << RESET << ' ';
	}
}
