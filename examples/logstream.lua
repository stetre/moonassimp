#!/usr/bin/env lua
-- MoonAssimp example: logstream.lua

ai = require("moonassimp")

function Usage()
   print("\nUsage: " .. arg[0] .. " <modelfile> [logstream]" ..
         "\n       logstream = stdout | stderr | file | user (defaults=stdout)\n") 
end
   
filename = arg[1]
logstream = arg[2] or 'stdout'
if not filename then Usage() return end

if logstream == 'stdout' or logstream == 'stderr' then
   ai.attach_log_stream(logstream)
elseif logstream == 'file' then
   ai.attach_log_stream('file', "mylogfile.log")
elseif logstream == 'user' then
   ai.attach_log_stream("user", function(message) print("MYLOGFUNC", message) end)
else
   Usage()
   return
end

ai.enable_verbose_logging(true)

scene = ai.import_file(filename, "triangulate", "join identical vertices", "sort by p type")

