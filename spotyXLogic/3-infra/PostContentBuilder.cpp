#include "PostContentBuilder.h"
#include <string>
#include <map>
#include <QByteArray>
#include <sstream>
#include <QString>
#include <QTextCodec>
using namespace std;
void infra::PostContentBuilder::add(std::string k, std::string v)
{
    QByteArray z = QByteArray::fromStdString(v).toPercentEncoding();
    QString DataAsString = QTextCodec::codecForUtfText(z)->toUnicode(z);
    auto data = make_pair(k,DataAsString.toStdString());
    table.insert(data);
}

QByteArray infra::PostContentBuilder::getAssembled()const
{
    stringstream ss;
    auto last = --table.end();
    for(auto iter = table.begin(); iter!=table.end(); ++iter)
    {
        string key = (*iter).first;
        string value = (*iter).second;
        ss<<key<<"="<<value;
        if(iter!=last)
        {
            ss<<"&";
        }

    }
    QByteArray result = QByteArray::fromStdString(ss.str());
    return result;
}
