include_files = {
    "**/*.lua",
    "extra/dist/tarantoolctl.in",
}

exclude_files = {
    "build/**/*.lua",
    "src/box/lua/serpent.lua", -- third-party source code
    "test/app/*.lua",
    "test/app-tap/lua/serializer_test.lua",
    "test/box/**/*.lua",
    "test/engine/*.lua",
    "test/engine_long/*.lua",
    "test/long_run-py/**/*.lua",
    "test/vinyl/*.lua",
    "test/replication/*.lua",
    "test/sql/*.lua",
    "test/swim/*.lua",
    "test/xlog/*.lua",
    "test/wal_off/*.lua",
    "test/var/**/*.lua",
    "test-run/**/*.lua",
    "third_party/**/*.lua",
    ".rocks/**/*.lua",
    ".git/**/*.lua",
}

files["extra/dist/tarantoolctl.in"] = {
	globals = {"box", "_TARANTOOL"},
	ignore = {"212/self", "122", "431"}
}
files["**/*.lua"] = {
	globals = {"box", "_TARANTOOL", "help", "tutorial"},
	ignore = {"212/self", "122", "143", "142"}
}
files["src/lua/*.lua"] = {ignore = {"212/self"}}
files["src/lua/init.lua"] = {globals = {"dostring"}}
files["src/lua/swim.lua"] = {ignore = {"431"}}
files["src/box/lua/console.lua"] = {ignore = {"212"}}
files["src/box/lua/load_cfg.lua"] = {ignore = {"542"}}
files["src/box/lua/net_box.lua"] = {ignore = {"431", "432", "411"}}
files["src/box/lua/schema.lua"] = {globals = {"tonumber64"}, ignore = {"431", "432"}}
