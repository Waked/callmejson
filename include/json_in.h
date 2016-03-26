#ifndef JSON_IN_H
#define JSON_IN_H

std::string readWord(std::ifstream&);
std::string nextKey(std::ifstream&, bool = 0);
ElementType nextValue(std::ifstream&);
void readObject(std::ifstream&, Object&);
bool loadJSON(std::ifstream&, Object&);

#endif // JSON_IN_H
