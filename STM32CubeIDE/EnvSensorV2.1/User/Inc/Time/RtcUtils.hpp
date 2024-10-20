#ifndef RTC_UTILS_HPP_
#define RTC_UTILS_HPP_

#include <Time/DateTime.hpp>

class RtcUtils {

public:
	static DateTime getCurrentDateTime();
	static void updateDateTime(DateTime dateTime);
};

#endif /* RTC_UTILS_HPP_ */
