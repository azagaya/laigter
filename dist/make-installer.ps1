# Builds laigter-setup.exe, a self extracting exe that unpacks laigter next to
# itself and starts it with --staged, so laigter offers to install or to stay
# portable.
#
# Runs windeployqt first, so all it needs is a built laigter.exe. Works the same
# on a dev machine and on the github runner.
#
# Usage, from the repo root:
#   powershell -ExecutionPolicy Bypass -File dist\make-installer.ps1
#   powershell -ExecutionPolicy Bypass -File dist\make-installer.ps1 -Exe release\laigter.exe

param(
    # Built laigter.exe. The newest one under the repo is used when empty
    [string]$Exe = "",
    [string]$DeployDir = "laigter-windows",
    [string]$OutFile = "laigter-setup.exe",
    # Folder with windeployqt, like C:\Qt\6.10.2\mingw_64\bin. Only needed when
    # Qt is not on the path, as it is on the github runner
    [string]$QtBin = "",
    # Folder with the mingw runtime dlls. Looked for next to Qt when empty
    [string]$MingwBin = "",
    [string]$SfxModule = "$PSScriptRoot\7zsd.sfx",
    # Icon for the setup exe itself, the module ships with its own
    [string]$Icon = "$PSScriptRoot\..\icons\laigter_icon.ico",
    # 9 is smallest, 1 is fastest, useful while testing
    [int]$Compression = 9,
    # Use an already prepared DeployDir instead of running windeployqt again
    [switch]$SkipDeploy
)

$ErrorActionPreference = "Stop"

# Replaces the icon of a pe file, so the setup exe looks like laigter and not
# like the sfx module
function Set-ExeIcon($exe, $ico)
{
    if (-not ([System.Management.Automation.PSTypeName]'Win32.PeResource').Type)
    {
        Add-Type -Namespace Win32 -Name PeResource -MemberDefinition @"
[DllImport("kernel32.dll", SetLastError=true, CharSet=CharSet.Unicode)]
public static extern IntPtr BeginUpdateResource(string fileName, bool deleteExisting);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern bool UpdateResource(IntPtr update, IntPtr type, IntPtr name, ushort language, byte[] data, uint size);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern bool EndUpdateResource(IntPtr update, bool discard);
[DllImport("kernel32.dll", SetLastError=true, CharSet=CharSet.Unicode)]
public static extern IntPtr LoadLibraryEx(string fileName, IntPtr file, uint flags);
[DllImport("kernel32.dll")]
public static extern bool FreeLibrary(IntPtr module);
public delegate bool EnumName(IntPtr module, IntPtr type, IntPtr name, IntPtr param);
public delegate bool EnumLang(IntPtr module, IntPtr type, IntPtr name, ushort language, IntPtr param);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern bool EnumResourceNames(IntPtr module, IntPtr type, EnumName callback, IntPtr param);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern bool EnumResourceLanguages(IntPtr module, IntPtr type, IntPtr name, EnumLang callback, IntPtr param);
"@
    }

    $RT_ICON = [IntPtr]3
    $RT_GROUP_ICON = [IntPtr]14

    # Replace the group the module already has instead of adding a second one,
    # or the shell is free to keep showing the old icon
    $script:groups = @()
    $langCb = [Win32.PeResource+EnumLang]{
        param($m, $t, $n, $l, $p)
        $script:groups += @{ Id = $n; Lang = $l }
        return $true
    }
    $nameCb = [Win32.PeResource+EnumName]{
        param($m, $t, $n, $p)
        [void][Win32.PeResource]::EnumResourceLanguages($m, $t, $n, $langCb, [IntPtr]::Zero)
        return $true
    }
    $module = [Win32.PeResource]::LoadLibraryEx($exe, [IntPtr]::Zero, 0x2)
    if ($module -ne [IntPtr]::Zero)
    {
        [void][Win32.PeResource]::EnumResourceNames($module, $RT_GROUP_ICON, $nameCb, [IntPtr]::Zero)
        [void][Win32.PeResource]::FreeLibrary($module)
    }
    if ($script:groups.Count -eq 0) { $script:groups = @(@{ Id = [IntPtr]1; Lang = [uint16]0 }) }

    $bytes = [System.IO.File]::ReadAllBytes($ico)
    $images = [BitConverter]::ToUInt16($bytes, 4)

    # The group is the same header plus one 14 byte entry per image, where the
    # last field is the id of the RT_ICON holding the pixels
    $group = New-Object System.IO.MemoryStream
    $writer = New-Object System.IO.BinaryWriter($group)
    $writer.Write([UInt16]0)
    $writer.Write([UInt16]1)
    $writer.Write([UInt16]$images)

    $handle = [Win32.PeResource]::BeginUpdateResource($exe, $false)
    if ($handle -eq [IntPtr]::Zero) { throw "Could not open $exe to set the icon" }

    $language = [uint16]$script:groups[0].Lang

    for ($i = 0; $i -lt $images; $i++)
    {
        $entry = 6 + $i * 16
        $size = [BitConverter]::ToUInt32($bytes, $entry + 8)
        $offset = [BitConverter]::ToUInt32($bytes, $entry + 12)

        $image = New-Object byte[] $size
        [Array]::Copy($bytes, $offset, $image, 0, $size)
        [void][Win32.PeResource]::UpdateResource($handle, $RT_ICON, [IntPtr]($i + 1), $language, $image, $size)

        # first 12 bytes are shared with the file entry, then the id. Copy them
        # into a real byte array, a powershell slice is an object array and
        # BinaryWriter then writes a single byte instead of the twelve
        $header = New-Object byte[] 12
        [Array]::Copy($bytes, $entry, $header, 0, 12)
        $writer.Write($header, 0, 12)
        $writer.Write([UInt16]($i + 1))
    }

    $writer.Flush()
    $group_bytes = $group.ToArray()
    foreach ($existing in $script:groups)
    {
        [void][Win32.PeResource]::UpdateResource($handle, $RT_GROUP_ICON, $existing.Id,
                                                 [uint16]$existing.Lang, $group_bytes, $group_bytes.Length)
    }

    if (-not [Win32.PeResource]::EndUpdateResource($handle, $false))
    {
        throw "Could not write the icon into $exe"
    }

    Write-Host ("Icon set from {0}, {1} sizes, on group {2}" -f
                (Split-Path $ico -Leaf), $images, $script:groups[0].Id.ToInt64())
}

function Find-Tool($name, $fallback)
{
    $found = (Get-Command $name -ErrorAction SilentlyContinue).Source
    if ($found) { return $found }
    if ($fallback -and (Test-Path $fallback)) { return $fallback }
    return $null
}

$sevenZip = Find-Tool "7z" "C:\Program Files\7-Zip\7z.exe"
if (-not $sevenZip) { throw "7z.exe not found, install 7-Zip" }

if (-not $SkipDeploy)
{
    # The built exe. On the runner it is release\laigter.exe, on a dev machine
    # it is somewhere under build\
    if (-not $Exe)
    {
        $candidate = Get-ChildItem . -Recurse -Filter "laigter.exe" -ErrorAction SilentlyContinue |
            Where-Object { $_.FullName -notlike "*\$DeployDir\*" } |
            Sort-Object LastWriteTime -Descending | Select-Object -First 1
        if (-not $candidate) { throw "No built laigter.exe found, build it first or pass -Exe" }
        $Exe = $candidate.FullName
    }
    if (-not (Test-Path $Exe)) { throw "No such file: $Exe" }

    # Packing a laigter older than the sources is confusing, it fails later with
    # things like an unknown command line option
    $newest_source = Get-ChildItem main.cpp, src, gui -Recurse -Include *.cpp, *.h -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if ($newest_source -and (Get-Item $Exe).LastWriteTime -lt $newest_source.LastWriteTime)
    {
        Write-Warning ("{0} is older than {1}, build laigter again or the setup will pack an old one" -f $Exe, $newest_source.Name)
    }

    # Given, or on the path as on the runner, or wherever qmake says
    $windeployqt = $null
    if ($QtBin) { $windeployqt = Join-Path $QtBin "windeployqt.exe" }
    if (-not $windeployqt -or -not (Test-Path $windeployqt))
    {
        $windeployqt = Find-Tool "windeployqt" $null
    }
    if (-not $windeployqt)
    {
        $qmake = Find-Tool "qmake" $null
        if ($qmake)
        {
            $bins = (& $qmake -query QT_INSTALL_BINS).Trim()
            $windeployqt = Join-Path $bins "windeployqt.exe"
        }
    }
    if (-not $windeployqt -or -not (Test-Path $windeployqt))
    {
        throw "windeployqt not found, pass -QtBin C:\Qt\<version>\mingw_64\bin"
    }

    # The mingw runtimes are not in the Qt folder but in the Tools one next to
    # it, so C:\Qt\6.10.2\mingw_64\bin means C:\Qt\Tools\mingw*\bin
    if (-not $MingwBin)
    {
        $qt_root = Split-Path (Split-Path (Split-Path $windeployqt -Parent) -Parent) -Parent
        $tools = Join-Path $qt_root "Tools"
        if (Test-Path $tools)
        {
            $MingwBin = Get-ChildItem $tools -Directory -Filter "mingw*" |
                ForEach-Object { Join-Path $_.FullName "bin" } |
                Where-Object { Test-Path (Join-Path $_ "libgomp-1.dll") } |
                Select-Object -Last 1
        }
    }

    Write-Host "Deploying $Exe"
    if (Test-Path $DeployDir) { Remove-Item $DeployDir -Recurse -Force }
    New-Item -ItemType Directory $DeployDir | Out-Null
    Copy-Item $Exe (Join-Path $DeployDir "laigter.exe")

    # We render with opengl, the direct3d shader compiler is never loaded. Old
    # windeployqt versions do not know the flag, so only pass it when it exists
    $deploy_args = @("--compiler-runtime", "--dir", $DeployDir)
    if ((& $windeployqt --help 2>&1) -match "no-system-dxc-compiler")
    {
        $deploy_args += "--no-system-dxc-compiler"
    }
    $deploy_args += (Join-Path $DeployDir "laigter.exe")

    & $windeployqt $deploy_args | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "windeployqt failed" }

    # windeployqt knows nothing about openmp, and misses some mingw runtimes
    foreach ($dll in @("libgomp-1.dll", "libwinpthread-1.dll", "libstdc++-6.dll", "libgcc_s_seh-1.dll"))
    {
        if (Test-Path (Join-Path $DeployDir $dll)) { continue }

        $found = $null
        if ($MingwBin -and (Test-Path (Join-Path $MingwBin $dll)))
        {
            $found = Join-Path $MingwBin $dll
        }
        else
        {
            $found = (where.exe $dll 2>$null | Select-Object -First 1)
        }

        if ($found) { Copy-Item $found $DeployDir }
        else { Write-Warning "$dll not found, laigter may not start on another machine" }
    }
}

if (-not (Test-Path (Join-Path $DeployDir "laigter.exe")))
{
    throw "$DeployDir has no laigter.exe"
}

# The sfx module that understands InstallPath and RunProgram. The one shipped
# with 7-Zip only extracts, it cannot start anything afterwards
if (-not (Test-Path $SfxModule))
{
    $release = "https://github.com/chrislake/7zsfxmm/releases/download/1.7.1.3901/7zsd_171_3901.7z"
    Write-Host "Downloading the sfx module from $release"

    $archive = Join-Path $env:TEMP "7zsd.7z"
    $unpacked = Join-Path $env:TEMP "7zsd"
    Invoke-WebRequest -Uri $release -OutFile $archive
    & $sevenZip x $archive "-o$unpacked" -y | Out-Null

    $found = Get-ChildItem $unpacked -Recurse -Filter "7zsd.sfx" | Select-Object -First 1
    if (-not $found) { throw "7zsd.sfx not found inside $release" }
    Copy-Item $found.FullName $SfxModule
}

# No InstallPath, so the module unpacks into a temp folder and removes it once
# laigter quits. %%T is that folder and %%S is where the setup exe was run
# from, which laigter uses as the default for a portable copy
$config = @"
;!@Install@!UTF-8!
Title="Laigter"
RunProgram="\"%%T\\laigter.exe\" --staged --from \"%%S\""
;!@InstallEnd@!
"@

# No BOM, the module reads this as plain utf8
$configPath = Join-Path $env:TEMP "laigter-sfx-config.txt"
[System.IO.File]::WriteAllText($configPath, $config, (New-Object System.Text.UTF8Encoding($false)))

# The payload has to sit at the root of the archive, not inside a folder.
# The sfx module only knows plain lzma, so no lzma2, no bcj2 filter and no
# compressed header, otherwise it stops with an unsupported method error
Write-Host "Packing $DeployDir"
$payload = Join-Path $env:TEMP "laigter-payload.7z"
if (Test-Path $payload) { Remove-Item $payload }
# Absolute, or 7z keeps the folder name in front of every path and laigter ends
# up one folder deeper than the sfx expects
$deploy_full = (Resolve-Path $DeployDir).Path
& $sevenZip a -t7z -m0=lzma -mf=off -mhc=off "-mx=$Compression" $payload (Join-Path $deploy_full "*") | Out-Null
if ($LASTEXITCODE -ne 0) { throw "7z failed to pack $DeployDir" }

# sfx module + config + payload, in that order, is the whole installer
if (-not [System.IO.Path]::IsPathRooted($OutFile))
{
    $OutFile = Join-Path (Get-Location).Path $OutFile
}
if (Test-Path $OutFile) { Remove-Item $OutFile }

# Patch a copy, the cached module stays as downloaded
$module = $SfxModule
if (Test-Path $Icon)
{
    $module = Join-Path $env:TEMP "laigter-7zsd.exe"
    Copy-Item $SfxModule $module -Force
    Set-ExeIcon $module (Resolve-Path $Icon).Path
}
else
{
    Write-Warning "$Icon not found, the setup will keep the sfx module icon"
}

$output = [System.IO.File]::Create($OutFile)
foreach ($part in @($module, $configPath, $payload))
{
    # not $input, that one is a powershell automatic variable
    $part_stream = [System.IO.File]::OpenRead($part)
    $part_stream.CopyTo($output)
    $part_stream.Close()
}
$output.Close()

Remove-Item $payload
"{0} is ready, {1:N1} MB" -f $OutFile, ((Get-Item $OutFile).Length / 1MB)
