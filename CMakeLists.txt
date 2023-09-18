cmake_minimum_required (VERSION 3.9)

project (YAWN)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	set (CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()

option (YAWN_PROD_BUILD "Enable production build" OFF)

add_subdirectory ("ThirdParty")

add_executable (BinaryToHeader "Source/Tools/BinaryToHeader.cpp")

file (GLOB_RECURSE GLSL_SOURCE_FILES "Source/*.vert" "Source/*.frag" "Source/*.comp" "Source/*.spv")
foreach (GLSL_SRC ${GLSL_SOURCE_FILES})
	get_filename_component (FILE_DIRECTORY ${GLSL_SRC} DIRECTORY)
	get_filename_component (FILE_NAME ${GLSL_SRC} NAME)
	get_filename_component (FILE_EXT ${GLSL_SRC} EXT)

	set (GLSL_H "${FILE_DIRECTORY}/Generated/${FILE_NAME}.h")

	string (REPLACE "." "_" VARIABLE_NAME ${FILE_NAME})

	add_custom_command (
		OUTPUT ${GLSL_H}
		COMMAND BinaryToHeader ${GLSL_SRC} ${GLSL_H} "${VARIABLE_NAME}" # GLSL -> C Header
		DEPENDS ${GLSL_SRC}
	)
	list (APPEND GLSL_BINARY_FILES ${GLSL_H})
endforeach (GLSL_SRC)
add_custom_target (Shaders DEPENDS ${GLSL_BINARY_FILES})

set (SRC 
	"Source/Core/Guid.cpp"
	"Source/Core/Memory.cpp"
	"Source/Core/Number.cpp"
	"Source/Core/Random.cpp"
	"Source/Core/String.cpp"
	"Source/Core/StringBuilder.cpp"
	"Source/Core/Unicode.cpp"
	"Source/Editor/Importers/ModelImporter.cpp"
	"Source/Editor/Importers/PrefabImporter.cpp"
	"Source/Editor/Importers/TextureImporter.cpp"
	"Source/Editor/Editor.cpp"
	"Source/Graphics/Color.cpp"
	"Source/Graphics/Compute.cpp"
	"Source/Graphics/Image.cpp"
	"Source/Graphics/ImageInfo.cpp"
	"Source/Graphics/Mesh.cpp"
	"Source/Graphics/Renderer.cpp"
	"Source/Graphics/RendererDriver.cpp"
	"Source/Graphics/S3TC.cpp"
	"Source/Graphics/Shader.cpp"
	"Source/Graphics/Texture.cpp"
	"Source/Graphics/Vertex.cpp"
	"Source/IO/File.cpp"
	"Source/IO/FileInfo.cpp"
	"Source/IO/Path.cpp"
	"Source/Math/Math.cpp"
	"Source/Math/Matrix4.cpp"
	"Source/Math/Vector2.cpp"
	"Source/Math/Vector3.cpp"
	"Source/Math/Vector4.cpp"
	"Source/Platform/Input.cpp"
	"Source/Platform/Window.cpp"
	"Source/Reflection/Field.cpp"
	"Source/Reflection/Type.cpp"
	"Source/Reflection/Types.cpp"
	"Source/Runtime/Loaders/TextureLoader.cpp"
	"Source/Runtime/Application.cpp"
	"Source/Runtime/Buffer.cpp"
	"Source/Runtime/Console.cpp"
	"Source/Runtime/JSON.cpp"
	"Source/Runtime/Main.cpp"
	"Source/Runtime/Object.cpp"
	"Source/Runtime/Pool.cpp"
	"Source/Runtime/Reactive.cpp"
	"Source/Runtime/Reference.cpp"
	"Source/Runtime/ResourceManager.cpp"
	"Source/Runtime/Settings.cpp"
	"Source/Runtime/Variant.cpp"
	"Source/Runtime/YTXT.cpp"
	"Source/Scene/Camera3D.cpp"
	"Source/Scene/Geometry3D.cpp"
	"Source/Scene/Node.cpp"
	"Source/Scene/Node3D.cpp"
	"Source/Scene/Scene.cpp"
	"Source/Threading/ConditionVariable.cpp"
	"Source/Threading/ExclusiveLock.cpp"
	"Source/Threading/ReadWriteLock.cpp"
	"Source/Threading/ThreadPool.cpp"

	"Source/Drivers/GLFW/WindowDriverGLFW.cpp"
	
	"Source/Drivers/OpenGL/RendererDriverOpenGL.cpp"
)

if (WIN32)
	set (SRC ${SRC}
		"Source/Drivers/Win32/ConditionVariableWin32.cpp"
		"Source/Drivers/Win32/DirectoryWin32.cpp"
		"Source/Drivers/Win32/ExclusiveMutexWin32.cpp"
		"Source/Drivers/Win32/FileWin32.cpp"
		"Source/Drivers/Win32/PathWin32.cpp"
		"Source/Drivers/Win32/ReadWriteMutexWin32.cpp"
		"Source/Drivers/Win32/ThreadWin32.cpp"
	)
endif ()

add_library (YAWN STATIC ${SRC})
target_compile_features (YAWN PUBLIC cxx_std_20)
target_include_directories (YAWN PUBLIC "Include")
target_link_libraries (YAWN PRIVATE json-c miniz imgui meshoptimizer rgbcx cgltf stb glew glfw)
add_dependencies (YAWN Shaders)

if (MSVC)
	target_compile_definitions (YAWN PRIVATE _CRT_SECURE_NO_WARNINGS)
endif ()

target_compile_definitions (YAWN PUBLIC YAWN_PROD_BUILD=$<BOOL:${YAWN_PROD_BUILD}>)

add_subdirectory ("Example")
