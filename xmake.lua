if is_os("windows") then
    set_config("arch", "x86")
    if(is_mode("release")) then
        set_config("vs_runtime", "MD")
        add_cxflags("-MD", {force = true})
        set_installdir("build/windows/x86/release")
    else
        set_config("vs_runtime", "MDd")
        add_cxflags("-MDd", {force = true})
        set_installdir("build/windows/x86/debug")
    end
else
    add_cxflags("-MD", {force = true})
end

target("block_queue")
    set_kind("binary")
    set_symbols("debug")
    
    add_includedirs("sources")
    add_files("sources/*.cpp")
    after_build(function(target)
        import("target.action.install")(target)
    end)