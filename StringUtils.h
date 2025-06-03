#pragma once

#include <string>

int MoveToPreviousWord(const std::string& str, int pos);
int MoveToNextWord(const std::string& str, int pos);

void DeleteWordBackward(std::string& str, int& pos);
void DeleteWordForward(std::string& str, int& pos);
