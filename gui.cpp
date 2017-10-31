#include <QApplication>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QLabel>
#include <iostream>

QString getSourceData(const QApplication &app) {

    QLabel *prompt = new QLabel;
    prompt->setText("Выполните этот запрос в Битриксе, и вставьте вместо него результат-страницу\n"
                            "!! НЕ ЗАБУДЬТЕ вывести все записи на страницу !!");

    QTextEdit *textEdit = new QTextEdit;
    textEdit->setAcceptRichText(false);
    textEdit->insertPlainText("Солнцезащитные очки:\n"
                                      "\n"
                                      "SELECT \n"
                                      "  e.property_163 AS SEX\n"
                                      ", e.property_111 AS MATERIAL\n"
                                      ", COALESCE(e.property_187, 0) AS SHAPE\n"
                                      ", COALESCE(e.property_188, 0) AS COLOR\n"
                                      ", e.iblock_element_id\n"
                                      "FROM b_iblock_element_prop_s5 AS e\n"
                                      "INNER JOIN b_iblock_property_enum AS p111\n"
                                      "  ON e.property_111 = p111.id AND p111.property_id = 111\n"
                                      "INNER JOIN b_search_content AS c\n"
                                      "  ON c.ITEM_ID = e.iblock_element_id\n"
                                      "LEFT JOIN b_iblock_property_enum AS p163\n"
                                      "  ON e.property_163 = p163.id AND p163.property_id = 163\n"
                                      "LEFT JOIN b_iblock_property_enum AS p187\n"
                                      "  ON e.property_187 = p187.id AND p187.property_id = 187\n"
                                      "LEFT JOIN b_iblock_property_enum AS p188\n"
                                      "  ON e.property_188 = p188.id AND p188.property_id = 188\n"
                                      "LEFT JOIN b_iblock_property_enum AS p112\n"
                                      "  ON e.property_112 = p112.id AND p112.property_id = 112;\n"
                                      "\n"
                                      "---------------------------------------------------------------\n"
                                      "\n"
                                      "Медицинские очки:\n"
                                      "\n"
                                      "SELECT \n"
                                      "  e.property_174 AS SEX\n"
                                      ", e.property_115 AS MATERIAL\n"
                                      ", COALESCE(e.property_192, 0) AS SHAPE\n"
                                      ", COALESCE(e.property_191, 0) AS COLOR\n"
                                      ", COALESCE(e.property_190, 0) AS O_TYPE\n"
                                      ", e.iblock_element_id\n"
                                      "FROM b_iblock_element_prop_s5 AS e\n"
                                      "INNER JOIN b_iblock_property_enum AS p115\n"
                                      "  ON e.property_115 = p115.id AND p115.property_id = 115\n"
                                      "INNER JOIN b_search_content AS c\n"
                                      "  ON c.ITEM_ID = e.iblock_element_id\n"
                                      "INNER JOIN b_iblock_property_enum AS p174\n"
                                      "  ON e.property_174 = p174.id AND p174.property_id = 174\n"
                                      "LEFT JOIN b_iblock_property_enum AS p192\n"
                                      "  ON e.property_192 = p192.id AND p192.property_id = 192\n"
                                      "LEFT JOIN b_iblock_property_enum AS p191\n"
                                      "  ON e.property_191 = p191.id AND p191.property_id = 191\n"
                                      "LEFT JOIN b_iblock_property_enum AS p190\n"
                                      "  ON e.property_190 = p190.id AND p190.property_id = 190\n"
                                      "LEFT JOIN b_iblock_property_enum AS p112\n"
                                      "  ON e.property_112 = p112.id AND p112.property_id = 112;");

    QPushButton *quitButton = new QPushButton("&Далее...");
    QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(prompt);
    layout->addWidget(textEdit);
    layout->addWidget(quitButton);

    QWidget window;
    window.setLayout(layout);
    window.setWindowTitle("Шаг 1: получение данных");
    window.resize(800, 600);
    window.show();

    app.exec();

    return textEdit->toPlainText();
}

void showOutputSqlStep1(const QApplication &app) {
    QLabel *prompt = new QLabel;
    prompt->setText("Выполните этот запрос в Битриксе (ЗАПРОС №1)");

    QTextEdit *textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    textEdit->insertPlainText("DELETE FROM b_iblock_element_prop_m5 WHERE IBLOCK_PROPERTY_ID = 122;");

    QPushButton *quitButton = new QPushButton("&Далее...");
    QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(prompt);
    layout->addWidget(textEdit);
    layout->addWidget(quitButton);

    QWidget window;
    window.setLayout(layout);
    window.setWindowTitle("Шаг 2: Удаление предыдущей информации о похожих");
    window.resize(800, 600);
    window.show();

    app.exec();
}

void showOutputSqlStep2(const QApplication &app, std::vector<std::pair<int, int>> out_vec) {

    QLabel *prompt = new QLabel;
    prompt->setText("Выполните этот запрос в Битриксе (ЗАПРОС №2)");

    QTextEdit *textEdit = new QTextEdit;
    textEdit->setReadOnly(true);

    auto sz = out_vec.size();
    QString sql_insert;
    for (int i = 0; i < sz; i++)
        sql_insert += QString("INSERT b_iblock_element_prop_m5 "
                                      "(IBLOCK_ELEMENT_ID,IBLOCK_PROPERTY_ID,VALUE,VALUE_NUM) "
                                      "VALUES (%1, 122, %2, %2);\n")
                .arg(out_vec[i].first)
                .arg(out_vec[i].second);

    textEdit->insertPlainText(sql_insert);

    QPushButton *quitButton = new QPushButton("&Далее...");
    QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(prompt);
    layout->addWidget(textEdit);
    layout->addWidget(quitButton);

    QWidget window;
    window.setLayout(layout);
    window.setWindowTitle("Шаг 3: Вставка новых данных о похожих");
    window.resize(800, 600);
    window.show();

    app.exec();
}

void showOutputSqlStep3(const QApplication &app) {
    QLabel *prompt = new QLabel;
    prompt->setText("Выполните этот запрос в Битриксе (ЗАПРОС №3)");

    QTextEdit *textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    textEdit->insertPlainText("UPDATE b_iblock_element_prop_s5 s5\n"
                                      "JOIN (\n"
                                      "  SELECT \n"
                                      "    IBLOCK_ELEMENT_ID\n"
                                      "  , CONCAT(\n"
                                      "      'a:3:{s:5:\"VALUE\";a:3:{i:'\n"
                                      "      , GROUP_CONCAT(CONCAT(cast(r.row_number - 1 as CHAR), ';s:6:\"', CAST(r.value as CHAR)) SEPARATOR '\";i:')\n"
                                      "      , '\";}s:11:\"DESCRIPTION\";a:3:{i:'\n"
                                      "      , GROUP_CONCAT(CONCAT(cast(r.row_number - 1 as CHAR), ';s:0:\"') SEPARATOR '\";i:')\n"
                                      "      , '\";}s:2:\"ID\";a:3:{i:'\n"
                                      "      , GROUP_CONCAT(CONCAT(cast(r.row_number - 1 as CHAR), ';s:6:\"', CAST(r.ID as CHAR)) SEPARATOR '\";i:')\n"
                                      "      , '\";}}'\n"
                                      "    ) prop\n"
                                      "  FROM \n"
                                      "  (\n"
                                      "    SELECT a.IBLOCK_ELEMENT_ID, a.VALUE, a.ID, count(*) as row_number \n"
                                      "    FROM b_iblock_element_prop_m5 a\n"
                                      "    JOIN b_iblock_element_prop_m5 b ON a.IBLOCK_ELEMENT_ID = b.IBLOCK_ELEMENT_ID AND a.VALUE >= b.VALUE\n"
                                      "    WHERE a.IBLOCK_PROPERTY_ID = 122 AND  b.IBLOCK_PROPERTY_ID = 122\n"
                                      "    GROUP BY a.IBLOCK_ELEMENT_ID, a.VALUE, a.ID\n"
                                      "  ) r\n"
                                      "  GROUP BY IBLOCK_ELEMENT_ID\n"
                                      ") f ON s5.iblock_element_id = f.IBLOCK_ELEMENT_ID\n"
                                      "SET s5.property_122 = f.prop;");

    QPushButton *quitButton = new QPushButton("&Далее...");
    QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(prompt);
    layout->addWidget(textEdit);
    layout->addWidget(quitButton);

    QWidget window;
    window.setLayout(layout);
    window.setWindowTitle("Шаг 4: Применение информации для отображения на сайте");
    window.resize(800, 600);
    window.show();

    app.exec();
}