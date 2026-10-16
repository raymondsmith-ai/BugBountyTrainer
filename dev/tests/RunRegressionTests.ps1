Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

if (-not (Get-Command cl.exe -ErrorAction SilentlyContinue)) {
    throw 'Open Developer PowerShell for Visual Studio, then run this script again.'
}

$projectRoot = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$testBuild = Join-Path ([System.IO.Path]::GetTempPath()) ('BBT-Regression-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $testBuild | Out-Null
$testExecutable = Join-Path $testBuild 'BBTRegressionTests.exe'
$sourceFiles = @(
    (Join-Path $projectRoot 'dev/tests/RegressionTests.cpp')
    (Join-Path $projectRoot 'dev/src/Researcher.cpp')
    (Join-Path $projectRoot 'dev/src/Challenge.cpp')
    (Join-Path $projectRoot 'dev/src/Lab.cpp')
    (Join-Path $projectRoot 'dev/src/LearningModule.cpp')
    (Join-Path $projectRoot 'dev/src/SaveManager.cpp')
)

Push-Location $testBuild
try {
    & cl.exe /nologo /std:c++20 /EHsc /W4 $sourceFiles "/Fe:$testExecutable"
    if ($LASTEXITCODE -ne 0) {
        throw 'Regression test compilation failed.'
    }
    & $testExecutable
    if ($LASTEXITCODE -ne 0) {
        throw 'Regression tests failed. Review the [FAIL] lines above.'
    }
    Write-Host "Tests passed. Executable: $testExecutable"
}
finally {
    Pop-Location
}
