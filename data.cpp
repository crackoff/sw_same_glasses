#include <cstdlib>
#include <vector>
#include <CL/cl_platform.h>
#include <QtCore>
#include <iostream>

using namespace std;

bool validateSunglassRow(vector<cl_int>);

vector<vector<cl_int>> getSunglassData(const QString src_data) {

    vector<vector<cl_int>> ret;

    auto lines = src_data.split('\n');

    bool is_data = false;

    // Отключение форматировния кода из-за ошибки в CLion
    // @formatter:off
    foreach(auto line, lines) {
        if (is_data) {
            auto values = line.split('\t');
            if (values.size() != 5) continue;

            vector<cl_int> row;
            for (int i = 0; i < 5; i++) {
                row.push_back(values[i].toInt());
            }

            if (!validateSunglassRow(row)) {

                cout << "Unprocessed row: ";
                for (int i = 0; i < row.size(); i++) cout << row[i] << ", ";
                cout << endl;

                continue;
            }

            ret.push_back(row);
        }

        // Признак начала данных - строка "iblock_element_id"
        if (line.contains("iblock_element_id"))
            is_data = true;
    }
    // @formatter:on

    return ret;
}

bool validateSunglassRow(vector<cl_int> row) {
    const int sexes[4] = {1200, 1201, 1202, 1219};
    const int materials[3] = {414, 415, 1124};
    const int shapes[6] = {1229, 1233, 1231, 1230, 1232, 1234};
    const int colors[16] = {1250, 1248, 1249, 1237, 1242, 1236, 1241, 1240,
                            1247, 1246, 1239, 1244, 1243, 1245, 1253, 1254};

    if (*find(begin(sexes), end(sexes), row[0]) != row[0]) return false;
    if (*find(begin(materials), end(materials), row[1]) != row[1]) return false;
    if (*find(begin(shapes), end(shapes), row[2]) != row[2]) return false;
    if (*find(begin(colors), end(colors), row[3]) != row[3]) return false;

    return true;
}