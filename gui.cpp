#include <QApplication>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QLabel>

QString showSelectSql(const QApplication &app) {

    QLabel *prompt = new QLabel;
    prompt->setText("Выполните этот запрос в Битриксе, и вставьте вместо него результат-страницу");

    QTextEdit *textEdit = new QTextEdit;
    textEdit->insertPlainText("SELECT \n"
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