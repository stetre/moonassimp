## MoonAssimp: Lua bindings for Assimp

MoonAssimp is a Lua binding library for the 
[Open Asset Import Library](http://www.assimp.org/).

It runs on GNU/Linux and on Windows (MSYS2/MinGW) and requires 
[Lua](http://www.lua.org/) (>=5.3) and 
[Assimp](http://www.assimp.org/main_downloads.html) (>=3.0).

_Authored by:_ _[Stefano Trettel](https://www.linkedin.com/in/stetre)_

[![Lua logo](./doc/powered-by-lua.gif)](http://www.lua.org/)

#### License

MIT/X11 license (same as Lua). See [LICENSE](./LICENSE).

#### Documentation

See the [Reference Manual](https://stetre.github.io/moonassimp/doc/index.html).

#### Getting and installing

Setup the build environment as described [here](https://github.com/stetre/moonlibs), then:

```sh
$ git clone https://github.com/stetre/moonassimp
$ cd moonassimp
moonassimp$ make
moonassimp$ make install # or 'sudo make install' (Ubuntu)
```

#### Example

The script below loads a scene from a 3D model file and prints the names of all
the nodes it contains:

```lua
-- MoonAssimp example: printnodenames.lua

ai = require("moonassimp")

filename = arg[1]
if not filename then print("Usage: " .. arg[0] .. " <modelfile>") return end

function print_node_names(node, indent) -- recursively prints the names of child nodes
   local indent = indent or "  "
   for _, child in ipairs(node:children()) do
      print(indent .. (child:name() or "???"))
      print_node_names(child, indent .. "  ")
   end
end

-- Import the scene from the model file:
scene, errmsg = ai.import_file(filename, "triangulate", "join identical vertices", "sort by p type")
-- Check that nothing went wrong:
assert(scene, errmsg) 
-- Get the root node and print the names of the nodes:
root = scene:root_node()
print(root:name())
print_node_names(root)

```

The script can be executed at the shell prompt with the standard Lua interpreter,
passing it a 3D model filename, e.g.:

```shell
$ lua printnodenames.lua mymodel.dae
```

Other examples can be found in the **examples/** directory.

#### See also

* [MoonLibs - Graphics and Audio Lua Libraries](https://github.com/stetre/moonlibs).

