#!/usr/bin/env lua
-- MoonAssimp example: versions.lua

ai = require("moonassimp")

print(ai._VERSION)
print(ai._ASSIMP_VERSION)
print(ai.get_version())
print(ai.get_legal_string())
print(ai.get_compile_flags())

print("MAX_FACE_INDICES", ai.MAX_FACE_INDICES)
print("MAX_BONE_WEIGHTS", ai.MAX_BONE_WEIGHTS)
print("MAX_VERTICES", ai.MAX_VERTICES)
print("MAX_FACES", ai.MAX_FACES)
print("MAX_NUMBER_OF_COLOR_SETS", ai.MAX_NUMBER_OF_COLOR_SETS)
print("MAX_NUMBER_OF_TEXTURECOORDS", ai.MAX_NUMBER_OF_TEXTURECOORDS)

print("is supported:", ai.is_extension_supported(".3ds"))
print("supported:", ai.get_extension_list())


-- To tokenize the extension list:
s = ai.get_extension_list()
t = {}
for v in string.gmatch(s, "%*%.(%w+);") do t[#t+1] = v end
print(table.concat(t, " "))

