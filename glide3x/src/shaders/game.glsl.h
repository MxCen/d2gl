#pragma once

"#ifdef VERTEX\n"
"layout(location=0) in vec2 Position;"
"layout(location=1) in vec2 TexCoord;"
"layout(location=2) in vec4 Color1;"
"layout(location=3) in vec4 Color2;"
"layout(location=4) in ivec2 TexIds;"
"layout(location=5) in ivec4 Flags;"
"uniform mat4 u_MVP;"
"out vec2 v_TexCoord;"
"out vec4 v_Color1,v_Color2;"
"flat out ivec2 v_TexIds;"
"flat out ivec4 v_Flags;"
"void main()"
"{"
  "gl_Position=u_MVP*vec4(Position,0,1);"
  "v_TexCoord=TexCoord;"
  "v_Color1=Color1.zyxw;"
  "v_Color2=Color2.wzyx;"
  "v_TexIds=TexIds;"
  "v_Flags=Flags;"
"}"
"\n#elif FRAGMENT\n"
"layout(location=0) out vec4 FragColor;"
"layout(location=1) out vec4 FragColorMap;layout(std140) uniform ubo_Colors{vec4 u_Palette[256];vec4 u_Gamma[256];};"
"uniform sampler2DArray u_Texture0,u_Texture1;"
"in vec2 v_TexCoord;"
"in vec4 v_Color1,v_Color2;"
"flat in ivec2 v_TexIds;"
"flat in ivec4 v_Flags;"
"void main()"
"{"
  "if(v_Flags.y==1)"
    "FragColor=v_Color2;"
  "else "
    "{"
      "FragColor=v_Color1;"
      "float v;"
      "v=v_TexIds.x==0?"
        "texture(u_Texture0,vec3(v_TexCoord,v_TexIds.y)).x:"
        "texture(u_Texture1,vec3(v_TexCoord,v_TexIds.y)).x;"
    "}"
"}"
"\n#endif"