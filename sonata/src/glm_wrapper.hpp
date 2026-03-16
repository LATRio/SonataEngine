#pragma once
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#endif
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/hash.hpp"
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#include "glm/gtc/type_ptr.hpp"
