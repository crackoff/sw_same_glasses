#ifndef SAME_GLASSES_DATA_H
#define SAME_GLASSES_DATA_H

#include <array>
#include <CL/cl_platform.h>

std::vector<std::vector<cl_int>> getGlassesData(const QString, bool *is_medical);

#endif //SAME_GLASSES_DATA_H
