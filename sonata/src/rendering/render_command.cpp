#include "render_command.hpp"
#include "opengl/opengl_renderer_api.hpp"

namespace Sonata {

RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}
