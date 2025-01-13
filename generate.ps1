     param (
    [switch] $Cleanup,   # Clean generated files
    [switch] $Build,     # Build binaries
    [switch] $Install,   # Install resources
    [switch] $VS2019,    # Visual studio 2019
    [switch] $NoCleanup # Don't clean
 )

function clearPrevious() 
{
    Write-Host "Deleting ./_solution." -ForegroundColor DarkRed 
    if (Test-Path -Path "$PSScriptRoot/_solution")
    {
        Remove-Item -Path "$PSScriptRoot/_solution" -Recurse -Force
    }

    Write-Host "Deleting ./_output." -ForegroundColor DarkRed 
    if (Test-Path -Path "$PSScriptRoot/_output")
    {
        Remove-Item -Path "$PSScriptRoot/_output" -Recurse -Force
    }

    Write-Host "Deleting ./imgui.ini" -ForegroundColor DarkRed 
    if (Test-Path -Path "$PSScriptRoot/imgui.ini")
    {
        Remove-Item -Path "$PSScriptRoot/imgui.ini" -Recurse -Force
    }
}

function generateSolution() 
{
    Write-Host "Creating ./_solution." -ForegroundColor DarkGreen 
    if (-Not(Test-Path -Path "$PSScriptRoot/_solution")) 
    {
        New-Item -ItemType Directory -Path "$PSScriptRoot/_solution"
    }

    Push-Location -Path  "$PSScriptRoot/_solution"

    Write-Host "Generating Visual Studio solution." -ForegroundColor DarkGreen

    if($VS2019)
    {
        cmake .. -G "Visual Studio 16 2019" -A x64
    }
    else
    {
        cmake .. -G "Visual Studio 17 2022" -A x64
    }
    
    Pop-Location
}

function compileProject()
{
    Push-Location -Path  "$PSScriptRoot/_solution"

    # Compile for Debug
    Write-Host "Compile for Debug." -ForegroundColor DarkYellow 
    cmake --build . --config Debug

    # Compile for Release
    Write-Host "Compile for Release." -ForegroundColor DarkYellow 
    cmake --build . --config Release

    Pop-Location
}

function installResources()
{
    Write-Host "Installing resources." -ForegroundColor DarkMagenta 

    # Clean for previous
    if (Test-Path -Path "$PSScriptRoot/build/debug/bin/Resources")
    {
        Remove-Item -Path "$PSScriptRoot/build/debug/bin/Resources" -Recurse -Force
    }

    if (Test-Path -Path "$PSScriptRoot/build/release/bin/Resources")
    {
        Remove-Item -Path "$PSScriptRoot/build/release/bin/Resources" -Recurse -Force
    }

    # Install for Debug
    Copy-Item -Path "$PSScriptRoot/resources" -Destination "$PSScriptRoot/build/debug/bin/Resources"   -Recurse -Force
    Copy-Item -Path "$PSScriptRoot/dlls/*"    -Destination "$PSScriptRoot/build/debug/bin"             -Recurse -Force

    # Install for Release
    Copy-Item -Path "$PSScriptRoot/resources" -Destination "$PSScriptRoot/build/release/bin/Resources" -Recurse -Force
    Copy-Item -Path "$PSScriptRoot/dlls/*"    -Destination "$PSScriptRoot/build/release/bin"           -Recurse -Force
}

# Entry point
if($Cleanup) 
{
    clearPrevious
}
else 
{
    Write-Host "Start project generation ..." -ForegroundColor DarkMagenta 
    
    generateSolution

    if($Build) 
    {
        compileProject
    }

    if($Install) 
    {
        installResources
    }

    Write-Host "... Done." -ForegroundColor DarkMagenta     
}