#ifndef  __CLION_IDE__

// Таблица похожести по полу
int constant sexes[4] = {1200, 1201, 1202, 1219};
int constant sex_s[4][4] = {{10, 0, 9, 0},
                            { 0,10, 9, 0},
                            { 9, 9,10, 0},
                            { 0, 0, 0,10}};

// Таблица похожести по форме
int constant shapes[6] = {1229,1233,1231,1230,1232,1234};
int constant shape_s[6][6] = {{10, 5, 1, 0, 3, 3},
                              { 5,10, 9, 3, 0, 0},
                              { 1, 9,10, 4, 6, 1},
                              { 0, 3, 4,10, 1, 7},
                              { 3, 0, 6, 1,10, 8},
                              { 3, 0, 1, 7, 8,10}};

// Таблица похожести по цвету
int constant colors[16] = {1250, 1248, 1249, 1237, 1242, 1236, 1241, 1240, 1247, 1246, 1239, 1244, 1243, 1245, 1253, 1254};
int constant color_s[16][16] = {{10, 9, 7, 0, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 2, 0},
                                { 9,10, 8, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0, 0, 1, 0},
                                { 7, 8,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 2, 0, 0},
                                { 0, 0, 0,10, 9, 0, 4, 0, 0, 3, 1, 0, 1, 0, 3, 0},
                                { 2, 0, 0, 9,10, 0, 4, 0, 0, 0, 1, 3, 3, 0, 7, 0},
                                { 0, 0, 0, 0, 0,10, 0, 0, 3, 2, 0, 0, 0, 2, 0, 6},
                                { 0, 0, 0, 4, 4, 0,10, 0, 0, 1, 6, 2, 0, 0, 0, 0},
                                { 0, 5, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0, 0, 0},
                                { 6, 1, 0, 0, 0, 3, 0, 0,10, 9, 0, 0, 0, 0, 0, 2},
                                { 0, 0, 0, 3, 0, 2, 1, 0, 9,10, 0, 0, 0, 0, 0, 0},
                                { 0, 0, 0, 1, 1, 0, 6, 0, 0, 0,10, 8, 3, 2, 1, 0},
                                { 0, 0, 0, 0, 3, 0, 2, 0, 0, 0, 8,10, 7, 1, 2, 0},
                                { 0, 0, 5, 1, 3, 0, 0, 0, 0, 0, 3, 7,10, 6, 1, 0},
                                { 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 1, 6,10, 0, 0},
                                { 2, 1, 0, 3, 7, 0, 0, 0, 0, 0, 1, 2, 1, 0,10, 0},
                                { 0, 0, 0, 0, 0, 6, 0, 0, 2, 0, 0, 0, 0, 0, 0,10}};

// Таблица похожести по материалу
int constant materials[3] = {414, 415, 1124};
int constant material_s[3][3] = {{10, 3, 7},
                                 { 3,10, 7},
                                 { 7, 7,10}};

// Опредедение мощностей по каждому из параметров сравнения
int constant sex_power = 1000;
int constant mat_power = 50;
int constant shape_power = 500;
int constant color_power = 100;

/*
 * Функция определения индекса элемента в массиве
 */
int indexOf(__constant int* arr, int len, int search) {
    for (int i = 0; i < len; i++)
        if (arr[i] == search)
            return i;

    return -1;
}

/*
 * Функция поиска похожих очков для магазина https://smartvision-optica.ru/
 */
__kernel void calc_the_sames (
        __global int *in,
        __global int *out,
        int t_cnt,
        int s_cnt) {

    int p_cnt = 5;
    size_t tid = get_global_id(0);
    int pid = tid * p_cnt;
    int oid = tid * s_cnt;

    // Смещения: 0 - пол, 1 - материал, 2 - форма, 3 - цвет
    int sex = indexOf(sexes, 4, in[pid + 0]);
    int mat = indexOf(materials, 3, in[pid + 1]);
    int shp = indexOf(shapes, 6, in[pid + 2]);
    int clr = indexOf(colors, 16, in[pid + 3]);

    // Обнуляем кэш и выходной буфер
    __local long si[4096];
    for (int i = 0; i < 4096; i++) si[i] = 0;
    for (int i = 0; i < s_cnt; i++) out[oid + i] = 0;

    for (int i = 0, ci = 0; i < t_cnt; i++) {
        if (i == tid) continue; // Не будем добавлять в похожие себя

        long cur = sex_s[sex][indexOf(sexes, 4, in[i * p_cnt + 0])] * sex_power;
        cur += material_s[mat][indexOf(materials, 3, in[i * p_cnt + 1])] * mat_power;
        cur += shape_s[shp][indexOf(shapes, 6, in[i * p_cnt + 2])] * shape_power;
        cur += color_s[clr][indexOf(colors, 16, in[i * p_cnt + 3])] * color_power;

        for (int j = 0; j < s_cnt; j++) {
            if (cur > si[j]) {
                si[j] = cur;
                out[oid + j] = in[i * p_cnt + 4];
                break;
            }
        }
    }
}

#endif