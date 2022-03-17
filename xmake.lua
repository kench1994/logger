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
add_requires("vcpkg::boost-system", {configs={runtime_link="shared", shared=true, debug=true}})
target("blockqueue")
    set_kind("binary")
    set_symbols("debug")
    
    add_includedirs("sources")
    add_headerfiles("sources/*.hpp")
    add_files("sources/*.cpp")
    add_packages("vcpkg::boost-system")
    after_build(function(target)
        import("target.action.install")(target)
    end)