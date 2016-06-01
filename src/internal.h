/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Stefano Trettel
 *
 * Software repository: MoonAssimp, https://github.com/stetre/moonassimp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/********************************************************************************
 * internal common header                                                       *
 ********************************************************************************/

#ifndef internalDEFINED
#define internalDEFINED

#include <string.h>
#include <stdlib.h>
#include "moonassimp.h"
#include "udata.h"

#define TOSTR_(x) #x
#define TOSTR(x) TOSTR_(x)

/* Note: all the dynamic symbols of this library (should) start with 'moonassimp_' .
 * The only exception is the luaopen_moonassimp() function, which is searched for
 * with that name by Lua.
 * MoonAssimp's string references on the Lua registry also start with 'moonassimp_'.
 */


/* Objects' metatabe names */
#define SCENE_MT "moonassimp_scene"
#define NODE_MT "moonassimp_node"
#define MESH_MT "moonassimp_mesh"
#define ANIMMESH_MT "moonassimp_animmesh"
#define MATERIAL_MT "moonassimp_material"
#define ANIMATION_MT "moonassimp_animation"
#define NODEANIM_MT "moonassimp_nodeanim"
#define MESHANIM_MT "moonassimp_meshanim"
#define TEXTURE_MT "moonassimp_texture"
#define LIGHT_MT "moonassimp_light"
#define CAMERA_MT "moonassimp_camera"
#define FACE_MT "moonassimp_face"
#define BONE_MT "moonassimp_bone"

/* internal type redefinitions */
#define scene_t struct aiScene
#define node_t struct aiNode
#define mesh_t struct aiMesh
#define animmesh_t struct aiAnimMesh
#define material_t struct aiMaterial
#define animation_t struct aiAnimation
#define nodeanim_t struct aiNodeAnim
#define meshanim_t struct aiMeshAnim
#define texture_t struct aiTexture
#define light_t struct aiLight
#define camera_t struct aiCamera
#define face_t struct aiFace
#define bone_t struct aiBone
#define texel_t struct aiTexel
#define vector2_t struct aiVector2D
#define vector3_t struct aiVector3D
#define color3_t struct aiColor3D
#define color4_t struct aiColor4D
#define quaternion_t struct aiQuaternion
#define matrix3_t struct aiMatrix3x3
#define matrix4_t struct aiMatrix4x4
#define aistring_t struct aiString


/* Userdata memory */
#define ud_t moonassimp_ud_t
typedef struct {
    void *obj; /* the object bound to this userdata */
    scene_t *scene; /* the scene it belongs to */
    mesh_t *mesh;   /* the mesh it belongs to (NULL if not applicable) */
    material_t *material; /* the material it belongs to (NULL if not applicable) */
    animation_t *animation; /* the animation it belongs to (NULL if not applicable) */
} moonassimp_ud_t;

#if 0
/* .c */
#define  moonassimp_
#endif

/* utils.c */
#define noprintf moonassimp_noprintf
int noprintf(const char *fmt, ...);
#define notavailable moonassimp_notavailable
int notavailable(lua_State *L, ...);
#define nilerrmsg moonassimp_nilerrmsg
int nilerrmsg(lua_State *L);
#define checkoption_hint moonassimp_checkoption_hint 
int checkoption_hint(lua_State *L, int arg, const char *def, const char *const lst[]);
#define checkboolean moonassimp_checkboolean
int checkboolean(lua_State *L, int arg);
#define optboolean moonassimp_optboolean
int optboolean(lua_State *L, int arg, int d);
#define checkindex moonassimp_checkindex
int checkindex(lua_State *L, int arg);
#define optindex moonassimp_optindex
int optindex(lua_State *L, int arg, int optval /* 0-based */);
#define pushindex moonassimp_pushindex
void pushindex(lua_State *L, int val);

#define pushvector2 moonassimp_pushvector2
int pushvector2(lua_State *L, vector2_t *vec, int astable);
#define pushvector3 moonassimp_pushvector3
int pushvector3(lua_State *L, vector3_t *vec, int astable);
#define pushcolor3 moonassimp_pushcolor3
int pushcolor3(lua_State *L, color3_t *col, int astable);
#define pushcolor4 moonassimp_pushcolor4
int pushcolor4(lua_State *L, color4_t *col, int astable);
#define pushquaternion moonassimp_pushquaternion
int pushquaternion(lua_State *L, quaternion_t *quat, int astable);
#define pushtexel moonassimp_pushtexel
int pushtexel(lua_State *L, texel_t *vec, int astable);
#define pushtexelf moonassimp_pushtexelf
int pushtexelf(lua_State *L, texel_t *vec, int astable);
#define pushmatrix3 moonassimp_pushmatrix3
int pushmatrix3(lua_State *L, matrix3_t *mat, int how);
#define pushmatrix4 moonassimp_pushmatrix4
int pushmatrix4(lua_State *L, matrix4_t *mat, int how);

#define newuserdata moonassimp_newuserdata
ud_t *newuserdata(lua_State *L, void *ptr, const char *mt);
#define freeuserdata moonassimp_freeuserdata
int freeuserdata(lua_State *L, void *ptr);
#define userdata(ptr) (ud_t*)udata_mem(ptr)
#define userdata_unref(L, ptr) udata_unref((L),(ptr))

/* animmesh.c */
#define newanimmesh moonassimp_newanimmesh
int newanimmesh(lua_State *L, scene_t *scene, mesh_t *mesh, animmesh_t *animmesh);
#define freeanimmesh moonassimp_freeanimmesh
int freeanimmesh(lua_State *L, animmesh_t *animmesh);
#define testanimmesh moonassimp_testanimmesh
animmesh_t* testanimmesh(lua_State *L, int arg);
#define checkanimmesh moonassimp_checkanimmesh
animmesh_t* checkanimmesh(lua_State *L, int arg);
#define pushanimmesh moonassimp_pushanimmesh
int pushanimmesh(lua_State *L, animmesh_t *p);


/* meshanim.c */
#define newmeshanim moonassimp_newmeshanim
int newmeshanim(lua_State *L, scene_t *scene, animation_t *animation, meshanim_t *meshanim);
#define freemeshanim moonassimp_freemeshanim
int freemeshanim(lua_State *L, meshanim_t *meshanim);
#define testmeshanim moonassimp_testmeshanim
meshanim_t* testmeshanim(lua_State *L, int arg);
#define checkmeshanim moonassimp_checkmeshanim
meshanim_t* checkmeshanim(lua_State *L, int arg);
#define pushmeshanim moonassimp_pushmeshanim
int pushmeshanim(lua_State *L, meshanim_t *p);


/* nodeanim.c */
#define newnodeanim moonassimp_newnodeanim
int newnodeanim(lua_State *L, scene_t *scene, animation_t *animation, nodeanim_t *nodeanim);
#define freenodeanim moonassimp_freenodeanim
int freenodeanim(lua_State *L, nodeanim_t *nodeanim);
#define testnodeanim moonassimp_testnodeanim
nodeanim_t* testnodeanim(lua_State *L, int arg);
#define checknodeanim moonassimp_checknodeanim
nodeanim_t* checknodeanim(lua_State *L, int arg);
#define pushnodeanim moonassimp_pushnodeanim
int pushnodeanim(lua_State *L, nodeanim_t *p);


/* face.c */
#define newface moonassimp_newface
int newface(lua_State *L, scene_t *scene, mesh_t *mesh, face_t *face);
#define freeface moonassimp_freeface
int freeface(lua_State *L, face_t *face);
#define testface moonassimp_testface
face_t* testface(lua_State *L, int arg);
#define checkface moonassimp_checkface
face_t* checkface(lua_State *L, int arg);
#define pushface moonassimp_pushface
int pushface(lua_State *L, face_t *p);


/* bone.c */
#define newbone moonassimp_newbone
int newbone(lua_State *L, scene_t *scene, mesh_t *mesh, bone_t *bone);
#define freebone moonassimp_freebone
int freebone(lua_State *L, bone_t *bone);
#define testbone moonassimp_testbone
bone_t* testbone(lua_State *L, int arg);
#define checkbone moonassimp_checkbone
bone_t* checkbone(lua_State *L, int arg);
#define pushbone moonassimp_pushbone
int pushbone(lua_State *L, bone_t *p);


/* animation.c */
#define newanimation moonassimp_newanimation
int newanimation(lua_State *L, scene_t *scene, animation_t *animation);
#define freeanimation moonassimp_freeanimation
int freeanimation(lua_State *L, animation_t *animation);
#define testanimation moonassimp_testanimation
animation_t* testanimation(lua_State *L, int arg);
#define checkanimation moonassimp_checkanimation
animation_t* checkanimation(lua_State *L, int arg);
#define pushanimation moonassimp_pushanimation
int pushanimation(lua_State *L, animation_t *p);


/* texture.c */
#define newtexture moonassimp_newtexture
int newtexture(lua_State *L, scene_t *scene, texture_t *texture);
#define freetexture moonassimp_freetexture
int freetexture(lua_State *L, texture_t *texture);
#define testtexture moonassimp_testtexture
texture_t* testtexture(lua_State *L, int arg);
#define checktexture moonassimp_checktexture
texture_t* checktexture(lua_State *L, int arg);
#define pushtexture moonassimp_pushtexture
int pushtexture(lua_State *L, texture_t *p);


/* light.c */
#define newlight moonassimp_newlight
int newlight(lua_State *L, scene_t *scene, light_t *light);
#define freelight moonassimp_freelight
int freelight(lua_State *L, light_t *light);
#define testlight moonassimp_testlight
light_t* testlight(lua_State *L, int arg);
#define checklight moonassimp_checklight
light_t* checklight(lua_State *L, int arg);
#define pushlight moonassimp_pushlight
int pushlight(lua_State *L, light_t *p);


/* camera.c */
#define newcamera moonassimp_newcamera
int newcamera(lua_State *L, scene_t *scene, camera_t *camera);
#define freecamera moonassimp_freecamera
int freecamera(lua_State *L, camera_t *camera);
#define testcamera moonassimp_testcamera
camera_t* testcamera(lua_State *L, int arg);
#define checkcamera moonassimp_checkcamera
camera_t* checkcamera(lua_State *L, int arg);
#define pushcamera moonassimp_pushcamera
int pushcamera(lua_State *L, camera_t *p);


/* material.c */
#define newmaterial moonassimp_newmaterial
int newmaterial(lua_State *L, scene_t *scene, material_t *material);
#define freematerial moonassimp_freematerial
int freematerial(lua_State *L, material_t *material);
#define testmaterial moonassimp_testmaterial
material_t* testmaterial(lua_State *L, int arg);
#define checkmaterial moonassimp_checkmaterial
material_t* checkmaterial(lua_State *L, int arg);
#define pushmaterial moonassimp_pushmaterial
int pushmaterial(lua_State *L, material_t *p);

/* mesh.c */
#define newmesh moonassimp_newmesh
int newmesh(lua_State *L, scene_t *scene, mesh_t *mesh);
#define freemesh moonassimp_freemesh
int freemesh(lua_State *L, mesh_t *mesh);
#define testmesh moonassimp_testmesh
mesh_t* testmesh(lua_State *L, int arg);
#define checkmesh moonassimp_checkmesh
mesh_t* checkmesh(lua_State *L, int arg);
#define pushmesh moonassimp_pushmesh
int pushmesh(lua_State *L, mesh_t *p);

/* node.c */
#define newnode moonassimp_newnode
int newnode(lua_State *L, scene_t *scene, node_t *node);
#define freenode moonassimp_freenode
int freenode(lua_State *L, node_t *node);
#define testnode moonassimp_testnode
node_t* testnode(lua_State *L, int arg);
#define checknode moonassimp_checknode
node_t* checknode(lua_State *L, int arg);
#define pushnode moonassimp_pushnode
int pushnode(lua_State *L, node_t *p);

/* scene.c */
#define newscene moonassimp_newscene
int newscene(lua_State *L, scene_t *scene);
#define testscene moonassimp_testscene
scene_t* testscene(lua_State *L, int arg);
#define checkscene moonassimp_checkscene
scene_t* checkscene(lua_State *L, int arg);
#define pushscene moonassimp_pushscene
int pushscene(lua_State *L, scene_t *p);

/* enums.c */
#define checkanimbehaviour moonassimp_checkanimbehaviour
unsigned int checkanimbehaviour(lua_State *L, int arg);
#define pushanimbehaviour moonassimp_pushanimbehaviour
int pushanimbehaviour(lua_State *L, unsigned int value);
#define checklogstream moonassimp_checklogstream
unsigned int checklogstream(lua_State *L, int arg);
#define pushlogstream moonassimp_pushlogstream
int pushlogstream(lua_State *L, unsigned int value);
#define checkblendmode moonassimp_checkblendmode
unsigned int checkblendmode(lua_State *L, int arg);
#define pushblendmode moonassimp_pushblendmode
int pushblendmode(lua_State *L, unsigned int value);
#define checkshadingmode moonassimp_checkshadingmode
unsigned int checkshadingmode(lua_State *L, int arg);
#define pushshadingmode moonassimp_pushshadingmode
int pushshadingmode(lua_State *L, unsigned int value);
#define checktexturetype moonassimp_checktexturetype
unsigned int checktexturetype(lua_State *L, int arg);
#define pushtexturetype moonassimp_pushtexturetype
int pushtexturetype(lua_State *L, unsigned int value);
#define checktexturemapping moonassimp_checktexturemapping
unsigned int checktexturemapping(lua_State *L, int arg);
#define pushtexturemapping moonassimp_pushtexturemapping
int pushtexturemapping(lua_State *L, unsigned int value);
#define checktexturemapmode moonassimp_checktexturemapmode
unsigned int checktexturemapmode(lua_State *L, int arg);
#define pushtexturemapmode moonassimp_pushtexturemapmode
int pushtexturemapmode(lua_State *L, unsigned int value);
#define checktextureop moonassimp_checktextureop
unsigned int checktextureop(lua_State *L, int arg);
#define pushtextureop moonassimp_pushtextureop
int pushtextureop(lua_State *L, unsigned int value);
#define checklightsourcetype moonassimp_checklightsourcetype
unsigned int checklightsourcetype(lua_State *L, int arg);
#define pushlightsourcetype moonassimp_pushlightsourcetype
int pushlightsourcetype(lua_State *L, unsigned int value);


/* bitfields.c */
#define checktextureflags moonassimp_checktextureflags
unsigned int checktextureflags(lua_State *L, int arg);
#define pushtextureflags moonassimp_pushtextureflags
int pushtextureflags(lua_State *L, unsigned int flags, int pushcode);
#define checkprimitivetype moonassimp_checkprimitivetype
unsigned int checkprimitivetype(lua_State *L, int arg);
#define pushprimitivetype moonassimp_pushprimitivetype
int pushprimitivetype(lua_State *L, unsigned int flags, int pushcode);
#define checksceneflags moonassimp_checksceneflags
unsigned int checksceneflags(lua_State *L, int arg);
#define pushsceneflags moonassimp_pushsceneflags
int pushsceneflags(lua_State *L, unsigned int flags, int pushcode);
#define checkpostprocessflags moonassimp_checkpostprocessflags
unsigned int checkpostprocessflags(lua_State *L, int arg);
#define pushpostprocessflags moonassimp_pushpostprocessflags
int pushpostprocessflags(lua_State *L, unsigned int flags, int pushcode);

/* main.c */
int luaopen_moonassimp(lua_State *L);
void moonassimp_open_import(lua_State *L);
void moonassimp_open_scene(lua_State *L);
void moonassimp_open_node(lua_State *L);
void moonassimp_open_mesh(lua_State *L);
void moonassimp_open_animmesh(lua_State *L);
void moonassimp_open_material(lua_State *L);
void moonassimp_open_animation(lua_State *L);
void moonassimp_open_texture(lua_State *L);
void moonassimp_open_light(lua_State *L);
void moonassimp_open_camera(lua_State *L);
void moonassimp_open_face(lua_State *L);
void moonassimp_open_bone(lua_State *L);
void moonassimp_open_nodeanim(lua_State *L);
void moonassimp_open_meshanim(lua_State *L);
void moonassimp_open_additional(lua_State *L);


/*------------------------------------------------------------------------------*
 | Debug and other utilities                                                    |
 *------------------------------------------------------------------------------*/

/* Dynamic referencing on the Lua registry */

#define reference(L, dst, arg) do {                 \
    lua_pushvalue((L), (arg));                      \
    (dst) = luaL_ref((L), LUA_REGISTRYINDEX);       \
} while(0)

#define unreference(L, ref) do {                    \
    if((ref)!=LUA_NOREF) {                          \
        luaL_unref((L), LUA_REGISTRYINDEX, (ref));  \
        (ref) = LUA_NOREF; }                        \
} while(0)

#define pushvalue(L, ref) /* returns LUA_TXXX */    \
    lua_rawgeti((L), LUA_REGISTRYINDEX, (ref)) 


/* If this is printed, it denotes a suspect bug: */
#define UNEXPECTED_ERROR "unexpected error (%s, %d)", __FILE__, __LINE__
#define unexpected(L) luaL_error((L), UNEXPECTED_ERROR)
#define NOT_AVAILABLE do { return luaL_error(L, "function not available"); } while(0)

#define badvalue(L,s)   lua_pushfstring((L), "invalid value '%s'", (s))

#define NOT_IMPLEMENTED(func)               \
static int func(lua_State *L)               \
    {                                       \
    luaL_error(L, "function "#func" is not implemented");   \
    return 0;                           \
    }

#define NOT_SUPPORTED(func)                 \
static int func(lua_State *L)               \
    {                                       \
    luaL_error(L, "function "#func" is not supported"); \
    return 0;                           \
    }

#if defined(DEBUG)

#define checkoption checkoption_hint
#define DBG printf

#define TR() do {                                           \
    printf("trace %s %d\n",__FILE__,__LINE__);              \
} while(0)

#define BK() do {                                           \
    printf("break %s %d\n",__FILE__,__LINE__);              \
    getchar();                                              \
} while(0)

#else 

#define checkoption luaL_checkoption
#define DBG noprintf
#define TR()
#define BK()

#endif /* DEBUG */

#endif /* internalDEFINED */
