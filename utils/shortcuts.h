//
// Created by enderqiu on 2018/11/2.
//

#ifndef VSLC_SHORTCUTS_H
#define VSLC_SHORTCUTS_H

#include <cstdlib>


extern bool verboseMode, shellMode;

/*
 * Abort execution unlike exit()
 */
void abort(int exitNumber, bool forceExit=false);

#endif //VSLC_SHORTCUTS_H
