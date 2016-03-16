#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Database {
private:
    vector<Property> m_props;
    vector<Object> m_objs;
    vector<Table> m_tabs;
    string m_name;
    int m_propertyCount;
    int m_objectCount;
    int m_tabCount;
public:
    string getName();
    bool setName(string);
    bool Properties();
};

int main()
{
    Database db;
    return 0;
}
