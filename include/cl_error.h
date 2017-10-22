#ifndef SAME_GLASSES_CL_ERROR_H
#define SAME_GLASSES_CL_ERROR_H

#include <CL/cl_platform.h>

const char *getErrorString(cl_int error);
void checkErr(cl_int error, const char *name);
void checkBuild(cl_int error, cl::Program program, cl::Device device);

#endif //SAME_GLASSES_CL_ERROR_H
