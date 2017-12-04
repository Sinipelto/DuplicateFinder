#include <iostream>
#include <QFile>
#include <QTextStream>
#include <vector>

using namespace std;

const QString SOURCE = "input.txt";
const QString DESTINATION = "output.txt";

int main()
{
    vector<QString> list = {};

    QFile input(SOURCE);
    QFile output(DESTINATION);

    if (!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "INPUT ERROR" << endl;
        return 1;
    }

    else if(!output.open(QIODevice::WriteOnly | QIODevice::Text)) {
        cout << "OUTPUT ERROR" << endl;
        return 1;
    }

    output.flush();

    unsigned count = 0;
    unsigned total = 0;

    while (!input.atEnd()) {
        bool flag = false;

        QString line = input.readLine().trimmed();

        for (auto i = list.begin(); i!=list.end();i++) {
            if (*i == line) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            list.push_back(line);

            QTextStream out(&output);
            out << line << endl;

            count++;
        }
        total++;
    }

//    for (auto i = list.begin();i!=list.end();i++) {
//        cout << "Item: " << i->toStdString() << endl;
//    }

    cout << "*** REPORT ***" << endl << endl;
    cout << count << " / " << total << " lines left" << endl;
    cout << (total - count) << " duplicates found" << endl;
    cout << "Clean output processed into output.txt." << endl;

    return 0;
}
