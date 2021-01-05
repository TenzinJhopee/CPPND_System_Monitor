#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds){
    int ss = seconds % 60;
    int hh = seconds / 3600;
    int mm = (seconds - hh * 3600) / 60;
    string SS = std::to_string(ss);
    SS = ss < 10 ? "0" + SS : SS;
    string MM = std::to_string(mm);
    MM = mm < 10 ? "0" + MM : MM;
    string HH = std::to_string(hh);

    return HH + ":" + MM + ":" + SS;
}