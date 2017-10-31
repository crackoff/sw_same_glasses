// Поиск похожих очков для магазина https://smartvision-optica.ru/
// (c) Oleg Krekov, 2017

#include <iostream>
#include <fstream>
#include <ctime>
#include <CL/cl.hpp>
#include <QApplication>
#include <QTextEdit>
#include "include/cl_error.h"
#include "include/data.h"
#include "include/gui.h"

using namespace std;

int main(int argv, char **args) {
    QApplication app(argv, args);

    bool is_medical;

    const int s_cnt = 5; // Количество похожих для поиска
    cl_int err; // Переменная для проверки ошибок

    ifstream file("program.cl");
    checkErr(file.is_open() ? CL_SUCCESS : 0xFF, "File program.cl is not found");

    auto src_data = getSourceData(app); // Показываем окно с SQL запросом и получаем первичные данные в виде страницы

    vector<vector<cl_int>> in_vec = getGlassesData(src_data, &is_medical); // Получаем исходные данные
    checkErr(in_vec.size() ? CL_SUCCESS : 0xFF, "Input data is empty");

    const int p_cnt = in_vec[0].size(); // Количество параметров для вычисления
    size_t len = in_vec.size(); // Количество элементов для вычисления
    cl_int in[len][p_cnt]; // Буфер с исходными данными
    cl_int out[len][s_cnt]; // Буфер для результата
    for (int i = 0; i < in_vec.size(); i++)
        for (int j = 0; j < in_vec[i].size(); j++)
            in[i][j] = in_vec[i][j];

    cout << "Input array length: " << in_vec.size() << ", setting params..." << endl;

    cl::Platform platforms[3];
    cl::Platform::get(platforms);
    cl_context_properties cprops[3] = {CL_CONTEXT_PLATFORM, (cl_context_properties) (platforms[0])(), 0};
    cl::Context context(CL_DEVICE_TYPE_GPU, cprops, NULL, NULL, &err);
    checkErr(err, "Context::Context()");

    vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    checkErr(devices.size() > 0 ? CL_SUCCESS : 0xFF, "devices.size() > 0");

    string prg(istreambuf_iterator<char>(file), (istreambuf_iterator<char>()));
    cl::Program::Sources source(1, make_pair(prg.c_str(), prg.length() + 1));
    cl::Program program(context, source);
    checkBuild(program.build(devices, ""), program, devices[0]);

    cl::Kernel kernel(program, is_medical ? "calc_the_sames_med" : "calc_the_sames", &err);
    checkErr(err, "Kernel::Kernel()");

    cl::Buffer inCL(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, p_cnt * len * sizeof(cl_int), in, &err);
    checkErr(err, "Buffer::Buffer(in)");
    cl::Buffer outCL(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, s_cnt * len * sizeof(cl_int), out, &err);
    checkErr(err, "Buffer::Buffer(out)");

    cl_uint arg = 0;
    err = kernel.setArg(arg++, inCL);
    checkErr(err, "Kernel::setArg(in)");
    err = kernel.setArg(arg++, outCL);
    checkErr(err, "Kernel::setArg(out)");
    kernel.setArg(arg++, len);
    checkErr(err, "Kernel::setArg(t_cnt)");
    kernel.setArg(arg++, s_cnt);
    checkErr(err, "Kernel::setArg(s_cnt)");

    cl::CommandQueue queue(context, devices[0], 0, &err);
    checkErr(err, "CommandQueue::CommandQueue()");

    cout << "Calculating started..." << endl;

    auto t = clock();

    // Будем выполнять поиск пачками по 100 записей
    auto step_count = ceil(in_vec.size() / 100.);
    for (unsigned i = 0; i < step_count; i++) {
        kernel.setArg(arg, i * 100);
        checkErr(err, "Kernel::setArg(i*100)");

        auto range = cl::NDRange(min(in_vec.size() - i * 100, 100u));
        cl::Event event;
        err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, range, cl::NDRange(1, 1), NULL, &event);
        checkErr(err, "CommandQueue::enqueueNDRangeKernel()");
        event.wait();

        cout << "Calculated step " << i << " of " << step_count << endl;
    }

    err = queue.enqueueReadBuffer(outCL, CL_TRUE, 0, len, out);
    checkErr(err, "CommandQueue::enqueueReadBuffer()");

    t = clock() - t;
    cout << endl << "Calculating completed in " << t << " ms." << endl;

    vector<pair<int, int>> out_vec;

    for (int i = 0; i < len; i++)
        for (int j = 0; j < s_cnt; j++)
            out_vec.push_back(pair<int, int>(in[i][p_cnt - 1], out[i][j]));

    // Отображаем выходные запросы поочередно
    showOutputSqlStep1(app);
    showOutputSqlStep2(app, out_vec);
    showOutputSqlStep3(app);

    cout << "Done. Press Enter to exit." << endl;

    file.close();
    getchar();
    return EXIT_SUCCESS;
}