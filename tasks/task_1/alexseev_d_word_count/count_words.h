#ifndef _COUNT_WORDS_H_
#define _COUNT_WORDS_H_

#include <string>
#include <mpi.h>
#include <ctime>
#include <sstream>

int countWords(std::string line, bool isWord);

int parallelCountWordsInString(const std::string& str);

std::string getRandString();

int getRandInt(int leftBorder, int rightBorder);

int sequentialCountWordsInString(const std::string& str);

#endif