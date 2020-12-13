lmake_compatibility_version(1)
function build()
    lmake_set_compiler("/bin/gcc")
    lmake_set_compiler_flags("-pthread -Iinclude")
    lmake_set_compiler_out("binaries/%.o")
    lmake_compile("src/main.c src/sched_disp.c src/timer.c src/clock.c src/loader.c src/tree.c")
    lmake_set_linker("/bin/gcc")
    lmake_set_linker_flags("-pthread")
    lmake_set_linker_out("binaries/seso")
    lmake_link("binaries/main.c.o binaries/sched_disp.c.o binaries/timer.c.o binaries/clock.c.o binaries/loader.c.o binaries/tree.c.o")
end
function builddebug()
    lmake_set_compiler("/bin/gcc")
    lmake_set_compiler_flags("-pthread -Iinclude -DDEBUG")
    lmake_set_compiler_out("binaries/%.o")
    lmake_compile("src/main.c src/sched_disp.c src/timer.c src/clock.c src/loader.c src/tree.c")
    lmake_set_linker("/bin/gcc")
    lmake_set_linker_flags("-pthread")
    lmake_set_linker_out("binaries/seso")
    lmake_link("binaries/main.c.o binaries/sched_disp.c.o binaries/timer.c.o binaries/clock.c.o binaries/loader.c.o binaries/tree.c.o")
end

function exec()
    build()
    lmake_exec("binaries/seso -p1 -m10 -t40 -c1")
end

function exec4()
    build()
    lmake_exec("binaries/seso -p10 -m10 -t40 -c4")
end

function exec4fast()
    build()
    lmake_exec("binaries/seso -p50 -m1 -t40 -c4")
end

function clean()
    lmake_exec("rm binaries/main.c.o binaries/sched_disp.c.o binaries/timer.c.o binaries/clock.c.o binaries/loader.c.o binaries/tree.c.o") 
end    
