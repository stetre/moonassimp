#!/usr/bin/env lua
-- MoonAssimp example: inspect3d.lua - 3D Model Inspector
-- 
-- For usage help, type at the shell prompt: 
-- $ ./inspect3d.lua --help

ai = require("moonassimp")

-- Set to false or comment out if you don't want verbose logging:
ai.enable_verbose_logging(true)

-- Uncomment/comment items if you want to change the default post-process flags:
DEFAULT_POSTPROCESSFLAGS = { 
-- 'calc tangent space',
   'join identical vertices',
-- 'make left handed',
   'triangulate',
-- 'remove component',
-- 'gen normals',
-- 'gen smooth normals',
-- 'split large meshes',
-- 'pre transform vertices',
-- 'limit bone weights',
-- 'validate data structure',
-- 'improve cache locality',
-- 'remove redundant materials',
-- 'fix infacing normals',
-- 'sort by p type',
-- 'find degenerates',
-- 'find invalid data',
-- 'gen uv coords',
-- 'transform uv coords',
-- 'find instances',
-- 'optimize meshes',
-- 'optimize graph',
-- 'flip uvs',
-- 'flip winding order',
-- 'split by bone count',
-- 'debone',
}

POSTPROCESSFLAGS = {
   { 'calc tangent space', '0x1' },
   { 'join identical vertices', '0x2' },
   { 'make left handed', '0x4' },
   { 'triangulate', '0x8' },
   { 'remove component', '0x10' },
   { 'gen normals', '0x20' },
   { 'gen smooth normals', '0x40' },
   { 'split large meshes', '0x80' },
   { 'pre transform vertices', '0x100' },
   { 'limit bone weights', '0x200' },
   { 'validate data structure', '0x400' },
   { 'improve cache locality', '0x800' },
   { 'remove redundant materials', '0x1000' },
   { 'fix infacing normals', '0x2000' },
   { 'sort by p type', '0x8000' },
   { 'find degenerates', '0x10000' },
   { 'find invalid data', '0x20000' },
   { 'gen uv coords', '0x40000' },
   { 'transform uv coords', '0x80000' },
   { 'find instances', '0x100000' },
   { 'optimize meshes', '0x200000' },
   { 'optimize graph', '0x400000' },
   { 'flip uvs', '0x800000' },
   { 'flip winding order', '0x1000000' },
   { 'split by bone count', '0x2000000' },
   { 'debone', '0x4000000' },
}

-- Utilities ------------------------------------------------------------------

function concatflags(t)
   if not t[1] then return "-" end
   return "'"..table.concat(t, "', '").. "'"
end

function concatboolean(val)
   if val==nil then return "-" end
   return tostring(val)
end

function concat2(a,b)
   if a==nil then return "-" end
   return "(" .. a ..", " .. b ..")"
end

function concatcolor(r, g, b, a)
   if not r then return "-" end
   if a then return string.format("{%.2f, %.2f, %.2f, %.2f}", r, g, b, a) end
   return string.format("{%.2f, %.2f, %.2f}", r, g, b)
end

function concatvec3(x, y, z)
   if not x then return "-" end
   return string.format("{%.1f, %.1f, %.1f}", x, y, z)
end

function concatvec2(x, y)
   if not x then return "-" end
   return string.format("{%.1f, %.1f}", x, y)
end

-- Print functions ------------------------------------------------------------

function PrintMesh(indent, mesh)
   print(indent .. "mesh: '" .. (mesh:name() or "???").."'")
   local indent = indent .. "  "
   print(indent .. "vertices:          " .. mesh:num_vertices())
   print(indent .. "normals:           " .. (mesh:has_normals() and "yes" or "no"))
   print(indent .. "tangents:          " .. (mesh:has_tangents() and "yes" or "no"))
   print(indent .. "faces:             " .. mesh:num_faces())
   print(indent .. "primitive types:   " .. concatflags({ai.primtypes(mesh:primitive_types())}))
   print(indent .. "bones:             " .. mesh:num_bones())
   print(indent .. "anim meshes:       " .. mesh:num_anim_meshes())
   local material = mesh:material() 
   print(indent .. "material:          '" .. material:name().."'")
-- print(indent .. "colors:            " .. (mesh:has_colors(1) and "yes" or "no"))
   local ncc = mesh:num_color_channels()
   print(indent .. "color channels:    " .. ncc)
-- print(indent .. "texture coords:    " .. (mesh:has_texture_coords(1) and "yes" or "no"))
   local ntc = mesh:num_texture_coords_channels()
   print(indent .. "texture channels:  " .. ntc)
   for i = 1,ntc do
      print(indent .. "  channel "..i.. " components: " .. mesh:num_texture_coords_components(i))
   end
end

function PrintNodes(node, indent)
   local indent = indent or ""
   print(indent .. "node: " .. "'".. (node:name() or "???") .. "' (" ..
      "children:".. node:num_children() .. ", meshes:".. node:num_meshes() ..")")
   for _, mesh in ipairs(node:meshes()) do PrintMesh(indent .. "  ", mesh) end
   for _, child in ipairs(node:children()) do
      PrintNodes(child, indent .. "  ")
   end
end
  
function PrintMaterial(material, indent)
   local indent = indent or ""
   print(indent .. "material: '" .. material:name() .."'")
   indent = indent .. "  "
   print(indent .. "twosided:          ".. concatboolean(material:twosided()))
   print(indent .. "wireframe:         ".. concatboolean(material:wireframe()))
   print(indent .. "blend:             ".. (material:blend() or "-"))
   print(indent .. "color_diffuse:     ".. concatcolor(material:color_diffuse()))
   print(indent .. "color_ambient:     ".. concatcolor(material:color_ambient()))
   print(indent .. "color_specular:    ".. concatcolor(material:color_specular()))
   print(indent .. "color_emissive:    ".. concatcolor(material:color_emissive()))
   print(indent .. "color_transparent: ".. concatcolor(material:color_transparent()))
   print(indent .. "color_reflective:  ".. concatcolor(material:color_reflective()))
   print(indent .. "opacity:           ".. (material:opacity() or "-"))
   print(indent .. "shininess:         ".. (material:shininess() or "-"))
   print(indent .. "shinpercent:       ".. (material:shinpercent() or "-"))
   print(indent .. "refraction:        ".. (material:refraction() or "-"))
   print(indent .. "bumpscaling:       ".. (material:bumpscaling() or "-"))
   print(indent .. "reflectivity:      ".. (material:reflectivity() or "-"))
   print(indent .. "shading:           ".. (material:shading() or "-"))
   print(indent .. "global_bg_image:   ".. ( material:global_bg_image() or "-"))

   local function PrintTexture(indent, tt, index) -- tt = texturetype
      print(indent .. "texture: " .. tt .. "[" .. index.."]")
      local indent = indent .. "  "
      print(indent .. "path:              " .. (material:texture_path(tt, index) or "-"))
      print(indent .. "channel:           " .. (material:texture_channel(tt, index) or "-"))
      print(indent .. "op:                " .. (material:texture_op(tt, index) or "-"))
      print(indent .. "mapping:           " .. (material:texture_mapping(tt, index) or "-"))
      print(indent .. "blend:             " .. (material:texture_blend(tt, index) or "-"))
      print(indent .. "mapmode (u,v):     " .. concat2(material:texture_mapmode(tt, index)))
      print(indent .. "axis:              " .. concatvec3(material:texture_axis(tt, index)))
      print(indent .. "translation:       " .. concatvec2(material:texture_translation(tt, index)))
      print(indent .. "scaling:           " .. concatvec2(material:texture_scaling(tt, index)))
      print(indent .. "rotation:          " .. (material:texture_rotation(tt, index) or "-"))
      local flags = material:texture_flags(tt, index)
      print(indent .. "textureflags:      " .. (flags and concatflags({ai.textureflags(flags)}) or "-"))
   end

   local function P(texturetype) 
      for i = 1,  material:texture_count(texturetype) do
         PrintTexture(indent, texturetype, i)
      end
   end
   P("diffuse")
   P("specular")
   P("ambient")
   P("emissive")
   P("height")
   P("normals")
   P("shininess")
   P("opacity")
   P("displacement")
   P("lightmap")
   P("reflection")
   P("unknown")
end  


function PrintEmbeddedTexture(texture, n, indent)
   local indent = indent or ""
   print(indent .. "embedded texture: " .. n)
   indent = indent .. "  "
   print(indent .. "compressed:     ".. concatboolean(texture:is_compressed()))
   print(indent .. "format_hint:    ".. (texture:format_hint() or "-"))
   print(indent .. "width:          ".. (texture:width() or "-"))
   print(indent .. "height:         ".. (texture:height() or "-"))
   print(indent .. "size (bytes):   ".. (texture:size() or "-"))
end  


function PrintLight(light, indent)
   local indent = indent or ""
   print(indent .. "light: '" .. light:name() .."'")
   indent = indent .. "  "
   print(indent .. "source_type:           ".. (light:source_type() or "-"))
   print(indent .. "attenuation_constant:  ".. (light:attenuation_constant() or "-"))
   print(indent .. "attenuation_linear:    ".. (light:attenuation_linear() or "-"))
   print(indent .. "attenuation_quadratic: ".. (light:attenuation_quadratic() or "-"))
   print(indent .. "angle_inner_cone:      ".. (light:angle_inner_cone() or "-"))
   print(indent .. "angle_outer_cone:      ".. (light:angle_outer_cone() or "-"))
   print(indent .. "position:              ".. concatvec3(light:position()))
   print(indent .. "direction:             ".. concatvec3(light:direction()))
   print(indent .. "color_diffuse:         ".. concatvec3(light:color_diffuse()))
   print(indent .. "color_specular:        ".. concatvec3(light:color_specular()))
   print(indent .. "color_ambient:         ".. concatvec3(light:color_ambient()))
end  


function PrintCamera(camera, indent)
   local indent = indent or ""
   print(indent .. "camera: '" .. camera:name() .."'")
   indent = indent .. "  "
   print(indent .. "aspect:                ".. (camera:aspect() or "-"))
   print(indent .. "clip_plane_near:       ".. (camera:clip_plane_near() or "-"))
   print(indent .. "clip_plane_far:        ".. (camera:clip_plane_far() or "-"))
   print(indent .. "horizontal_fov:        ".. (camera:horizontal_fov() or "-"))
   print(indent .. "position:              ".. concatvec3(camera:position()))
   print(indent .. "up:                    ".. concatvec3(camera:up()))
   print(indent .. "look_at:               ".. concatvec3(camera:look_at()))
end  


function PrintHelp()
   print("\nInspect a 3D model file using MoonAssimp and prints a report on stdout.\n")
   print("Usage:")
   print("  "..arg[0].." <filename> [postprocessflags]")
   print("  "..arg[0].." [option]")
   print("Options:")
   print("  --help  - print this help page")
   print("  --flags - list the postprocessflags")
   print("  --ext   - list the supported extensions")
   print("Examples:")
   print("  "..arg[0].." mymodel.obj           # use default flags")
   print("  "..arg[0].." mymodel.obj 0x8       # 'triangulate'")
   print("  "..arg[0].." mymodel.obj 0x8+0x20  # 'triangulate'+'gen normals'")
   print("  "..arg[0].." --flags               # list flags")
   print("  "..arg[0].." --ext                 # list extensions")
   print("")
end

-- Main -----------------------------------------------------------------------

if not arg[1] then
   PrintHelp() 
   return 
end

if arg[1]:sub(1,2) == "--" then -- options
   if arg[1] == "--help" then
      PrintHelp()
      return
   end
   if arg[1] == "--flags" then
      print("Post process flags:")
      for _,v in ipairs(POSTPROCESSFLAGS) do 
         print("- '"..v[1] .. "' = "..v[2])
      end
      return
   elseif arg[1] == "--ext" then
      print(ai.get_extension_list())
      return
   else
      print("invalid option '"..arg[1].."'")
      return
   end
end

filename = arg[1]

-- Determine the post-process flags to be used:
if arg[2] then 
   local flags = tonumber(arg[2])
   if not flags then 
      flags = load("return "..arg[2])()
   end
   postprocessflags = {ai.postprocessflags(flags)}
else
   postprocessflags = DEFAULT_POSTPROCESSFLAGS
end

-- Import the model:
scene, errmsg = ai.import_file(filename, table.unpack(postprocessflags))
assert(scene, errmsg)

-- Print the report:
print("======================================================================")
print("3D MODEL INSPECTION REPORT")
print("======================================================================")
print("model file:         " .. filename)
print("post process flags: ".. concatflags(postprocessflags))

print("\n-- Memory ------------------------------------------------------------")
mem = ai.get_memory_requirements(scene)

print("memory requirements (bytes):")
print("  total:      " .. mem.total)
print("  nodes:      " .. mem.nodes)
print("  meshes:     " .. mem.meshes)
print("  textures:   " .. mem.textures)
print("  materials:  " .. mem.materials)
print("  lights:     " .. mem.lights)
print("  cameras:    " .. mem.cameras)
print("  animations: " .. mem.animations)

print("\n-- Scene -------------------------------------------------------------")
flags = scene:flags()
print("sceneflags:   ".. concatflags({ai.sceneflags(flags)}))

print("scene contents:")
print("  meshes:     " .. scene:num_meshes())
print("  materials:  " .. scene:num_materials())
print("  textures:   " .. scene:num_textures())
print("  lights:     " .. scene:num_lights())
print("  cameras:    " .. scene:num_cameras())
print("  animations: " .. scene:num_animations())

root = scene:root_node()
print("\n-- Nodes -------------------------------------------------------------")
PrintNodes(root)

print("\n-- Materials ---------------------------------------------------------")
materials = scene:materials()
for k, material in ipairs(materials) do
   PrintMaterial(material)
   print()
end

print("\n-- Textures ----------------------------------------------------------")
textures = scene:textures()
for k, texture in ipairs(textures) do
   PrintEmbeddedTexture(texture, k)
   print()
end

print("\n-- Lights ------------------------------------------------------------")
lights = scene:lights()
for k, light in ipairs(lights) do
   PrintLight(light)
   print()
end

print("\n-- Cameras -----------------------------------------------------------")
cameras = scene:cameras()
for k, camera in ipairs(cameras) do
   PrintCamera(camera)
   print()
end

--[[ @@TODO:
print("\n-- Animations --------------------------------------------------------")
animations = scene:animations()
for k, animation in ipairs(animations) do
   PrintAnimation(animation)
   print()
end
--]]

print("\nEND OF REPORT")

