$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
$target = Join-Path $root "examples\answer.njbf"

# NJBF header: magic, format version, instruction count and global count.
$instructions = [uint32[]]@(
    0x01000028, # pushc 40
    0x01000002, # pushc 2
    0x02000000, # add
    0x08000000, # wrint
    0x0100000A, # pushc '\n'
    0x0A000000, # wrchr
    0x00000000  # halt
)

$stream = [IO.File]::Create($target)
$writer = [IO.BinaryWriter]::new($stream)
try {
    $writer.Write([Text.Encoding]::ASCII.GetBytes("NJBF"))
    $writer.Write([uint32]4)
    $writer.Write([uint32]$instructions.Count)
    $writer.Write([uint32]0)
    foreach ($instruction in $instructions) {
        $writer.Write($instruction)
    }
}
finally {
    $writer.Dispose()
}

Write-Host "Created $target"
