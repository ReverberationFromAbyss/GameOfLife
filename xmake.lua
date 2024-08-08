add_rules("mode.debug", "mode.release")

set_languages("c++23")
set_policy("build.c++.modules", true)

local std_module_SOURCE_DIR = "..\\..\\..\\..\\..\\PKGs\\Store\\PLE\\llvm-mingw-20240619-ucrt-x86_64\\share\\libc++\\v1"
target("std", function()
	set_kind("static")
	-- set_policy("build.merge_archive", true)
	if is_kind("shared") and is_plat("windows") then
		add_rules("utils.symbols.export_all", { export_classes = true })
	end

	set_policy("build.c++.modules.tryreuse.discriminate_on_defines", true)
	set_policy("build.c++.modules.culling", false)
	set_policy("build.c++.modules.std", false)

	on_config(function(target)
		local _, toolname = target:tool("cxx")
		if toolname:find("clang", 1, true) then
			target:add(
				"cxxflag",
				"-stdlib=libc++",
				"-Wno-reserved-module-identifier",
				"-Wno-reserved-user-defined-literal"
			)
			target:add("ldflags", "-stdlib=libc++", "-Wl,-rpath='.'")
			target:add(
				"files",
				std_module_SOURCE_DIR .. "\\std.cppm",
				std_module_SOURCE_DIR .. "\\std.compat.cppm",
				{ install = true }
			)
		end
	end)
end)

target("class-defination", function()
	set_kind("headeronly")
	add_rules("c++")
	add_headerfiles("src/**.inc")
end)

package("std", function()
	set_sourcedir(path.join(os.scriptdir(), "std_module_SOURCE_DIR"))
	on_install(function(package)
		import("package.tools.xmake").install(package, {})
	end)
end)

target("GameOfLife", function()
	set_kind("binary")

	on_config(function(target)
		local _, toolname = target:tool("cxx")
		if toolname:find("clang", 1, true) then
			target:add(
				"cxxflags",
				"-stdlib=libc++",
				"-Wno-reserved-module-identifier",
				"-Wno-reserved-user-defined-literal"
			)
			target:add("ldflags", "-stdlib=libc++", "-Wl,-rpath='.'")
			target:add("deps", "std")
			target:add("packages", "std")
			target:add("files", std_module_SOURCE_DIR .. "\\std.cppm", std_module_SOURCE_DIR .. "\\std.compat.cppm")
			--target:add_cxxflags("-stdlib=libc++",
			--  "-Wno-reserved-module-identifier",
			--  "-Wno-reserved-user-defined-literal")
			--target:add_ldflags("-stdlib=libc++",
			--  "-Wl,-rpath='.'")
			--target:add_deps("std")
			--target:add_packages("std")
			--target:add_files(std_module_SOURCE_DIR .. "\\std.cppm",
			--  std_module_SOURCE_DIR .. "\\std.compat.cppm")
			target:set("policy", "build.c++.modules.culling", false)
		end
		print(target:get("files"))
	end)

	add_deps("class-defination")
	add_files("src/main.cpp", "src/**.cc", "src/**.ixx")
end)
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--
