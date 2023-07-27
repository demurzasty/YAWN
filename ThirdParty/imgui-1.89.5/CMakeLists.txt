cmake_minimum_required (VERSION 3.19)

add_library (imgui STATIC
    "imgui.cpp"
    "imgui_demo.cpp"
    "imgui_draw.cpp"
    "imgui_tables.cpp"
    "imgui_widgets.cpp"
)
target_include_directories (imgui PUBLIC ".")
