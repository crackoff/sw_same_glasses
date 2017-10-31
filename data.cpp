#include <cstdlib>
#include <vector>
#include <CL/cl_platform.h>
#include <QtCore>
#include <iostream>

using namespace std;

bool validateSunglassRow(vector<cl_int>);
bool validateMedicalRow(vector<cl_int> row);

vector<vector<cl_int>> getGlassesData(const QString src_data, bool *is_medical) {

    vector<vector<cl_int>> ret;

    auto lines = src_data.split('\n');

    bool is_data = false;

    // Отключение форматировния кода из-за ошибки в CLion
    // @formatter:off
    foreach(auto line, lines) {
        if (is_data) {
            auto values = line.split('\t');
            int p_cnt = *is_medical ? 6 : 5;
            if (values.size() != p_cnt) continue;

            vector<cl_int> row;
            for (int i = 0; i < p_cnt; i++) {
                row.push_back(values[i].toInt());
            }

            bool valid = *is_medical ? validateMedicalRow(row) : validateSunglassRow(row);
            if (!valid) {

                cout << "Unprocessed row: ";
                for (int i = 0; i < row.size(); i++) cout << row[i] << ", ";
                cout << endl;

                continue;
            }

            ret.push_back(row);
        }

        // Признак медицинских оправ
        if (line.contains("O_TYPE"))
            *is_medical = true;

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

bool validateMedicalRow(vector<cl_int> row) {
    const int sexes[4] = {1208, 1209, 1210, 1220};
    const int materials[3] = {1203, 1204, 1212};
    const int shapes[6] = {1261, 1265, 1263, 1262, 1264, 1266};
    const int colors[16] = {1267, 1268, 1269, 1270, 1271, 1272, 1273, 1274,
                            1275, 1276, 1277, 1278, 1279, 1280, 1281, 1282};
    const int rim_glasses[3] = {1258, 1259, 1260};

    if (*find(begin(sexes), end(sexes), row[0]) != row[0]) return false;
    if (*find(begin(materials), end(materials), row[1]) != row[1]) return false;
    if (*find(begin(shapes), end(shapes), row[2]) != row[2]) return false;
    if (*find(begin(colors), end(colors), row[3]) != row[3]) return false;
    if (*find(begin(rim_glasses), end(rim_glasses), row[4]) != row[4]) return false;

    return true;
}