#ifndef __BUFFER_RENDER_COMMAND__
#define __BUFFER_RENDER_COMMAND__ 1

#include <rendercommand.h>
#include <vector>
#include <platform_types.h>

namespace VC {

	class BufferCommand : public RenderCommand {

	public:

		virtual ~BufferCommand();
		BufferCommand();

		virtual void Action() override;

		void SetVertices(float* newVertices, u32 numOfVertices);

	private:

		std::vector<float> vertices_;
		

	};

}

#endif // __RENDER_COMMAND__