#ifndef JSON_IN_H
#define JSON_IN_H

std::string readWord(std::ifstream&);
std::string readKey(std::ifstream&);
void toNextValue(std::ifstream&);
ElementType checkTypeOf(char);
bool isAtObjectEnd(std::ifstream&);
Element* readValueFrom(std::ifstream&);
Element* readKVPair(std::ifstream&, bool = 0);
void loadJSON(std::ifstream&, Object&);

#endif // JSON_IN_H
