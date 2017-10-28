#ifndef SAME_GLASSES_GUI_H
#define SAME_GLASSES_GUI_H

QString getSourceData(const QApplication &app);
void showOutputSqlStep1(const QApplication &app);
void showOutputSqlStep2(const QApplication &app, std::vector<std::pair<int, int>>);
void showOutputSqlStep3(const QApplication &app);

#endif //SAME_GLASSES_GUI_H
