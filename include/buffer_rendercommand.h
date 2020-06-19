#ifndef __BUFFER_RENDER_COMMAND__
#define __BUFFER_RENDER_COMMAND__ 1

#include <rendercommand.h>
#include <buffer.h>
#include <platform_types.h>

namespace VC {

	class BufferCommand : public RenderCommand {

	public:

		virtual ~BufferCommand();
		BufferCommand();

		virtual void Action() override;

		void setBuffer(u32 id);

	private:

		Buffer buffer_;
		

	};

}

#endif // __RENDER_COMMAND__