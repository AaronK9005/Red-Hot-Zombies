#pragma once

#include "pch.hpp"

GLenum glCheckError_(const char* file, const char* function, int line);

#define glCheckError() glCheckError_(__FILE__, __func__, __LINE__)