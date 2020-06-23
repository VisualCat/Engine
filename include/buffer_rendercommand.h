#ifndef __BUFFER_RENDER_COMMAND__
#define __BUFFER_RENDER_COMMAND__ 1

#include <rendercommand.h>
#include <geometry.h>
#include <platform_types.h>

namespace VC {

	class BufferCommand : public RenderCommand {

	public:

		virtual ~BufferCommand();
		BufferCommand();

		virtual void Action() override;

		void setGeometry(u32 id);

	private:

		Geometry geometry_;
		

	};

}

#endif // __RENDER_COMMAND__