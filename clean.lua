newaction {
    trigger = "clean",
    description = "clean files generated by premake5",
    execute = function()
        os.remove("**.vcxproj**")
        os.remove("**.sln")
        os.rmdir("./.vscode")
        os.rmdir("./.vs")
        os.rmdir("./Build")
    end
}