#ifndef __VC_GEOMETRY__
#define __VC_GEOMETRY__ 1

namespace VC {

  class Shader
  {
  public:

    void LoadSource(const char* filePath);
    const char* source();

  private:
    const char* source_;
  };

}


#endif // __VC_GEOMETRY___
