param(
	[string]$inFile = "",
	[string]$outFile = "",
	[switch]$help = $false)

if ($help) {
	write-host "usage: first.ps1 INPUT_FILE OUTPUT_FILE"
	write-host "This program enumerates lines of INPUT_FILE "
	write-host "and places them to OUTPUT_FILE."
	Exit
}

if ($inFile -eq "") {
	Throw "You must specify INPUT_FILE"
}

if ($outFile -eq "") {
	Throw "You must specify OUTPUT_FILE"
}

Write-Host "INPUT_FILE: $inFile"
Write-Host "OUTPUT_FILE: $outFile"
Write-Host ""

$fileContent = (get-content $inFile)

for ($i = 0; $i -lt $fileContent.Length; $i++) {
	$lineNum = $($i + 1)
	$fileContent[$i] = $("$lineNum" + ": " + $fileContent[$i])
	write-host $fileContent[$i]
}

$fileContent | out-file "$outFile"