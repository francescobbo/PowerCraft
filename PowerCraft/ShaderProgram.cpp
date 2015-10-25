#include "stdafx.h"
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
  _id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(_id);
}

void ShaderProgram::Attach(Shader &shader) {
  glAttachShader(_id, shader._id);
}

void ShaderProgram::Link() {
  glLinkProgram(_id);

  GLint success;
  glGetProgramiv(_id, GL_LINK_STATUS, &success);
  if (!success)
  {
	  char infoLog[512];
	  glGetProgramInfoLog(_id, 512, NULL, infoLog);
	  throw std::string("Unable to link shader program: ") + infoLog;
  }
}

void ShaderProgram::Use() {
  glUseProgram(_id);
  _vao.Bind();
}

void ShaderProgram::SetupAttribute(std::string attribute, int count, int type, int normalized, int stride, int offset) {
	GLint pos = glGetAttribLocation(_id, attribute.c_str());
	const void *offPtr = (const void *) offset;
	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, stride, offPtr);
	glEnableVertexAttribArray(pos);
}
