/* ============================================================
 * ShaderProgram.hpp: A shader program of OpenGL renderer.
 * ============================================================*/

#pragma once

#include <string>

namespace Pong 
{
	/// <summary>
	/// A shader program that has own vertex and fragment shader.
	/// </summary>
	class ShaderProgram {
		public:
			/// <summary>
			/// Create shader program.
			/// </summary>
			/// <param name="vertexPath">The path of a vertex shader.</param>
			/// <param name="fragmentPath">The path of a fragment shader.</param>
			ShaderProgram(const char* vertexPath, const char* fragmentPath);

			/// <summary>
			/// Delete this shader program.
			/// </summary>
			~ShaderProgram();

			/// <summary>
			/// Use this shader program.
			/// </summary>
			void use();

			/// <summary>
			/// Set vec2 value of a uniform variable.
			/// </summary>
			/// <param name="name">Name of an uniform variable.</param>
			/// <param name="value1">First value.</param>
			/// <param name="value2">Second value.</param>
			void setUniformVec2(const std::string& name, float value1, float value2);

			/// <summary>
			/// Return the id of this shader program assigned by OpenGL.
			/// </summary>
			/// <returns>Id of the shader program.</returns>
			inline unsigned int getId() const { return m_Id; }
		private:
			unsigned int m_Id;				//Id of this shader program.
	};
}