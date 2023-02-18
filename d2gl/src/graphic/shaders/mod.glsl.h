#pragma once

"#ifdef VERTEX\n"
"layout(location=0) in vec2 Position;"
"layout(location=1) in vec2 TexCoord;"
"layout(location=2) in vec4 Color1;"
"layout(location=3) in vec4 Color2;"
"layout(location=4) in ivec2 TexIds;"
"layout(location=5) in ivec4 Flags;"
"layout(location=6) in vec2 Extra;"
"uniform mat4 u_MVP;"
"out vec4 v_Position;"
"out vec2 v_TexCoord;"
"out vec4 v_Color1,v_Color2;"
"flat out ivec2 v_TexIds;"
"flat out ivec4 v_Flags;"
"out vec2 v_Extra;"
"void main()"
"{"
  "v_Position=u_MVP*vec4(Position,0,1);"
  "gl_Position=v_Position;"
  "v_TexCoord=TexCoord;"
  "v_Color1=Color1.wzyx;"
  "v_Color2=Color2.wzyx;"
  "v_TexIds=TexIds;"
  "v_Flags=Flags;"
  "v_Extra=Extra;"
"}"
"\n#elif FRAGMENT\n"
"layout(location=0) out vec4 FragColor;"
"uniform sampler2D u_Texture[16];"
"uniform sampler2DArray u_Textures[16];"
"in vec4 v_Position;"
"in vec2 v_TexCoord;"
"in vec4 v_Color1,v_Color2;"
"flat in ivec2 v_TexIds;"
"flat in ivec4 v_Flags;"
"in vec2 v_Extra;"
"uniform vec2 u_Size,u_Scale;"
"uniform vec4 u_TextMask;"
"uniform bool u_IsMasking=false;"
"float v(vec3 v,float i,float y)"
"{"
  "float u=max(min(v.x,v.y),min(max(v.x,v.y),v.z)),n=max(i,1.)*(u-1.+.5*y);"
  "return clamp(n+.5,0.,1.);"
"}"
"void main()"
"{"
  "switch(v_Flags.x){"
    "case 0:"
      "FragColor=texture(u_Texture[v_TexIds.x],v_TexCoord)*v_Color1;"
      "break;"
    "case 1:"
      "FragColor=texture(u_Textures[v_TexIds.x],vec3(v_TexCoord,v_TexIds.y))*v_Color1;"
      "break;"
    "case 2:"
      "FragColor=v_Color1;"
      "break;"
    "case 3:"
      "if(v_Flags.w==1)"
        "{"
          "float i=v(texture(u_Textures[v_TexIds.x],vec3(v_TexCoord,v_TexIds.y)).xyz,v_Extra.x,v_Extra.y+.05),y=v(texture(u_Textures[v_TexIds.x],vec3(v_TexCoord,v_TexIds.y)).xyz,v_Extra.x,.95);"
          "FragColor=vec4(mix(v_Color2.xyz,v_Color1.xyz,y),v_Color1.w*i);"
        "}"
      "else "
        "{"
          "float i=v(texture(u_Textures[v_TexIds.x],vec3(v_TexCoord,v_TexIds.y)).xyz,v_Extra.x,v_Extra.y);"
          "FragColor=vec4(v_Color1.xyz,v_Color1.w*i);"
        "}"
      "if(u_IsMasking&&v_Flags.z==0)"
        "if(u_TextMask.x<v_Position.x&&u_TextMask.z>v_Position.x&&u_TextMask.y>v_Position.y&&u_TextMask.w<v_Position.y)"
          "FragColor.w=0.;"
        "else "
           "FragColor.w*=.7;"
      "break;"
  "}"
  "float i=1.00001;"
  "vec2 s=vec2(i/u_Scale.x/v_Extra.x,i/u_Scale.y/v_Extra.y);"
  "switch(v_Flags.y){"
    "case 1:"
      "if(v_TexCoord.x<s.x||v_TexCoord.x>1.-s.x||v_TexCoord.y<s.y||v_TexCoord.y>1.-s.y)"
        "FragColor=v_Color2;"
    "case 2:"
      "vec2 n=s*2.,d=s*3.;"
      "if(v_TexCoord.x>n.x&&v_TexCoord.x<d.x||v_TexCoord.x<1.-n.x&&v_TexCoord.x>1.-d.x||v_TexCoord.y>n.y&&v_TexCoord.y<d.y||v_TexCoord.y<1.-n.y&&v_TexCoord.y>1.-d.y)"
        "FragColor=v_Color2;"
      "break;"
  "}"
"}"
"\n#endif"