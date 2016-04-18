#!/usr/bin/env lua

-- MoonAssimp example: printnodenames.lua

ai = require("moonassimp")

filename = arg[1]
if not filename then print("Usage: " .. arg[0] .. " <modelfile>") return end

--ai.attach_log_stream("stdout")
--ai.enable_verbose_logging(true)

scene, errmsg = ai.import_file(filename, "triangulate", "join identical vertices", "sort by type")
assert(scene, errmsg)

function print_node_names(node, indent)
   local indent = indent or "  "
   for _, child in ipairs(node:children()) do
      print(indent .. (child:name() or "???"))
      print_node_names(child, indent .. "  ")
   end
end

root = scene:root_node()
print(root:name())
print_node_names(root)

