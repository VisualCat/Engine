
#include <stdio.h>
#include <stdlib.h>
#include <shader.h>
#include <logger.h>

using namespace VC;

void Shader::LoadSource(const char* filePath)
{

  FILE* myFile = fopen(filePath, "rb");

  if (myFile == nullptr)
  {
    //printf("[ERROR] : Failed to load shader file from path (%s)\n", filePath);
    Logger::addMessage("Failed to load shader file");
  }
  else {
    fseek(myFile, 0, SEEK_END);

    long int fileSize = ftell(myFile);
    fseek(myFile, 0, SEEK_SET);

    char* code;
    code = (char*)malloc(fileSize * sizeof(char) + 1);
    code[fileSize] = '\0';

    fread(code, 1, fileSize, myFile);

    source_ = code;

    Logger::addMessage("Shader successfully load");

  }

}

const char* Shader::source()
{
  return source_;
}
