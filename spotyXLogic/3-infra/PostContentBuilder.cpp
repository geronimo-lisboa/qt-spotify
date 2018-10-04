#include "PostContentBuilder.h"
#include <string>
#include <map>
#include <QByteArray>
#include <
using namespace std;
void infra::PostContentBuilder::add(std::string k, std::string v)
{
    auto data = make_pair(k,v);
    table.insert(data);
}

QByteArray infra::PostContentBuilder::getAssembled()const
{
    QByteArray result;
    for_each(table.begin(), table.end(),[&result](pair<string, string> current){
        string key = current.first;
        string value = current.second;
    });
    return result;
}
