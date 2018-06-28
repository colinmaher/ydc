// $Id: debug.cpp,v 1.10 2018-01-25 14:05:16-08 - - $

#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#include "debug.h"
#include "util.h"

vector<bool> debugflags::flags (UCHAR_MAX + 1, false);

void debugflags::setflags (const string& initflags) {
   for (const unsigned char flag: initflags) {
      if (flag == '@') flags.assign (flags.size(), true);
                  else flags[flag] = true;
   }
   if (getflag ('x')) {
      string flag_chars;
      for (size_t index = 0; index < flags.size(); ++index) {
         if (getflag (index)) flag_chars += static_cast<char> (index);
      }
   }
}

//
// getflag -
//    Check to see if a certain flag is on.
//

bool debugflags::getflag (char flag) {
   return flags[static_cast<unsigned char> (flag)];
}

void debugflags::where (char flag, const char* file, int line,
                        const char* pretty_function) {
   note() << "DEBUG(" << flag << ") " << file << "[" << line << "] "
          << "   " << pretty_function << endl;
}

