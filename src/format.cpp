#include "format.h"

#include <iomanip>
#include <sstream>
#include <string>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  long seconds_elapsed = seconds % SECONDS_PER_MINUTE;
  long minutes_elapsed = (seconds / SECONDS_PER_MINUTE) % SECONDS_PER_MINUTE;
  long hours_elapsed = seconds / SECONDS_PER_HOUR;

  std::stringstream formated_string;

  formated_string << std::setw(2) << std::setfill('0') << hours_elapsed << ":"
                  << std::setw(2) << std::setfill('0') << minutes_elapsed << ":"
                  << std::setw(2) << std::setfill('0') << seconds_elapsed;

  return formated_string.str();
}